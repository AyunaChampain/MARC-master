#include <stdlib.h>
#include <stdio.h>
#include "bot.h"
#include "nbinarytree.h"
#include "map.h"
#include "node.h"
#include "loc.h"
#include "moves.h"

// Define constants
#define NUM_MOVES 7
#define RANDOM_POOL_SIZE 9

// Weighted moves
t_weighted_move weighted_moves[NUM_MOVES] = {
        {F_10, 22.0}, {F_20, 15.0}, {F_30, 7.0},
        {B_10, 7.0}, {T_LEFT, 21.0}, {T_RIGHT, 21.0}, {U_TURN, 7.0}
};


// Fonction choisissant un mouvement aléatoire
t_move choose_random_move(t_weighted_move moves[], int size)
{
    double total_weight = 0.0;

    // Calculer le poids total
    for (int i = 0; i < size; i++)
    {
        total_weight += moves[i].probability;
    }

    // Générer une valeur aléatoire dans la plage [0, total_weight)
    double random_value = ((double)rand() / RAND_MAX) * total_weight;

    // Sélectionner un mouvement en fonction du poids
    for (int i = 0; i < size; i++)
    {
        if (random_value < moves[i].probability)
        {
            // Réduit la probabilité
            moves[i].probability *= 0.99;
            return moves[i].move;
        }
        random_value -= moves[i].probability;
    }

    // Retour de secours
    return moves[0].move;
}


// Fonction qui génère un pool (de 9 mouvements)
void generate_random_moves_pool(t_move pool[], int pool_size, t_weighted_move moves[], int num_moves)
{
    for (int i = 0; i < pool_size; i++)
    {
        pool[i] = choose_random_move(moves, num_moves);
    }
}


// Fonction qui affiche les mouvements d'un pool
void print_moves_pool(t_move pool[], int pool_size)
{
    printf("Generated Moves Pool: ");
    for (int i = 0; i < pool_size; i++)
    {
        printf("%s ", getMoveAsString(pool[i])); // Assuming getMoveAsString converts move to a string
    }
    printf("\n\n");
}

//Fonction vérifiant la validité d'un mouvement
int isValidPosition(int x, int y, t_map map)
{
    return x >= 0 && x < map.x_max && y >= 0 && y < map.y_max;
}

// Fonction qui retire un mouvement d'un pool
void remove_move_from_pool(t_move pool[], int *pool_size, t_move move)
{
    for (int i = 0; i < *pool_size; i++)
    {
        //Si le mouvement cherché est dans le pool
        if (pool[i] == move)
        {
            // Récupère le dernier mouvement pour le mettre à la place
            pool[i] = pool[*pool_size - 1];
            (*pool_size)--; // Et réduit la taille du pool
            return;
        }
    }
}


// Fonction pour vérifier si un mouvement est valide dans le pool
int is_valid_move_in_pool(t_move move, t_move pool[], int pool_size)
{
    for (int i = 0; i < pool_size; i++)
    {
        if (pool[i] == move)
        {
            return 1;  // Le mouvement est valide, il est dans le pool
        }
    }
    return 0;  // Le mouvement n'est pas valide, il n'est pas dans le pool
}

//Fonction copiant le pool
void copy_pool(t_move dest[], t_move source[], int pool_size)
{
    for (int i = 0; i < pool_size; i++)
    {
        dest[i] = source[i];
    }
}

// Fonction récursive pour ajouter les voisins comme enfants dans l'arbre
void addNeighborsAsChildrenRecursive(p_nnode node, t_localisation loc, t_map map, int depth, int max_moves, t_move pool[], int pool_size, int reg) {

    //Si des paramètres ne sont pas valides, on retourne
    if (depth <= 0 || max_moves <= 0)
    {
        return;
    }

    // Créer une copie du pool pour cette branche récursive
    t_move pool_copy[pool_size];
    copy_pool(pool_copy, pool, pool_size);

    // Limiter à 4 enfants seulement si reg = 1
    int max_children;
    if (reg == 1)
    {
        max_children = 4;
    }
    else
    {
        max_children = 5;
    }

    // Itérer sur les mouvements possibles
    for (int i = 0; i < max_children; i++)
    {
        t_move mov = pool_copy[i];

        // Vérifier si le mouvement est valide
        if (is_valid_move_in_pool(mov, pool_copy, pool_size))
        {
            t_localisation next_loc = move(loc, mov);  // Calculer la nouvelle position en tenant compte de l'orientation

            // Vérifier si la position est valide dans la carte
            if (isValidPosition(next_loc.pos.x, next_loc.pos.y, map))
            {
                //Récupère le coût de la case concernée
                int cost = map.costs[next_loc.pos.y][next_loc.pos.x];

                // Créer un nœud avec la nouvelle position et orientation
                p_nnode child = createNode(cost, next_loc.pos.x, next_loc.pos.y, mov);
                child->ori = next_loc.ori;  // Mettre à jour l'orientation du robot dans le nœud enfant

                // Ajouter le nœud enfant au nœud actuel
                add_child(node, child);

                // Retirer le mouvement utilisé du pool copié afin d'éviter les répétitions de mouvements déjà utilisés
                remove_move_from_pool(pool_copy, &pool_size, mov);

                // Appel récursif pour ajouter les voisins pour le nœud enfant
                addNeighborsAsChildrenRecursive(child, next_loc, map, depth - 1, max_moves - 1, pool_copy, pool_size, reg);
            }
        }
    }
}


//Fonction créant un arbre
p_nnode buildTree(t_map map, int posx, int posy, int depth, int max_moves, t_move pool[], int pool_size, int reg)
{
    t_localisation start_loc = loc_init(posx, posy, NORTH); // Orientation de départ
    int root_cost = map.costs[posy][posx];

    // Nœud racine sans mouvement menant à lui (état initial)
    p_nnode root = createNode(root_cost, posx, posy, F_10);

    // Ajouter les voisins récursivement
    addNeighborsAsChildrenRecursive(root, start_loc, map, depth, max_moves, pool, pool_size, reg);

    return root;
}


// Fonction pour gérer les mouvements du robot
void move_robot_and_print(t_localisation *loc, t_move movement, t_map map, int* reg)
{
    //Récupère la nature du terrain
    t_soil terrain_type = map.soils[loc->pos.y][loc->pos.x];

    // Ajuster le mouvement en fonction du terrain
    if (terrain_type == ERG)
    {
        //Si le mouvement est un Erg, réduit d'un mouvement
        printf("Le robot a rencontre un Erg, reduction du mouvement") ;
        if (movement == F_10 || movement == B_10)
        {
            movement = 0;
        }
        else
        {
            if (movement == F_20)
            {
                movement = F_10;
            }
            else
            {
                if (movement == F_30) movement = F_20;
            }
        }
        if (movement == U_TURN)
        {
            movement = (rand() % 2) ? T_LEFT : T_RIGHT;
        }
        else
        {
            if (movement == T_RIGHT || movement == T_LEFT)
            {
                movement = 0;
            }
        }
    }

    // Calculer la nouvelle position en tenant compte de l'orientation
    t_localisation new_loc = move(*loc, movement);

    //Si la position est valide (dans la map)
    if (isValidPosition(new_loc.pos.x, new_loc.pos.y, map))
    {
        //Affiche les mouvements et les mets à jour
        if (movement == T_LEFT || movement == T_RIGHT || movement == U_TURN)
        {
            //printf("Turn: %s\n", getMoveAsString(movement));
            loc->ori = new_loc.ori; // Mise à jour de l'orientation uniquement
        }
        else
        {
            printf("Move: %s\n", getMoveAsString(movement));

            *loc = new_loc; // Mise à jour de la position et de l'orientation
        }
        printf("Updated position: (%d, %d), orientation: %d\n", loc->pos.x, loc->pos.y, loc->ori);
    }
    else
    {
        printf("Invalid move: The robot cannot move out of bounds to (%d, %d).\n", new_loc.pos.x, new_loc.pos.y);
    }

    //Si le terrain est un reg, la prochaine phase a seulement 4 mouvements
    if (terrain_type == REG)
    {
        printf("Robot has been shaken on Reg terrain. Limiting next phase to 4 moves.\n\n");
        *reg = 1;
    }
    else
    {
        printf("\n");
    }
}




// Fonction pour afficher le chemin
void print_path(p_nnode chemin[], int index)
{
    printf("Path to minimum node:\n");
    for (int i = 0; i < index; i++)
    {
        printf("Move: %s, Position: (%d, %d), Cost: %d\n",
               getMoveAsString(chemin[i]->movement),
               chemin[i]->x, chemin[i]->y, chemin[i]->value);
    }
}

void bot_function(struct s_map map, int x, int y)
{
    int cpt = 1;          // Compteur de phases
    int reg = 0;          // Indicateur pour terrain "Reg"
    int max_moves = 5;    // Nombre maximum de mouvements (modifiable)

    t_localisation loc = loc_init(x, y, NORTH);  // Position et orientation initiales

    // Génération du pool aléatoire de mouvements
    while (map.costs[loc.pos.y][loc.pos.x] != 0)
    {
        //Affiche la phase
        printf("\n=========================\n");
        printf("Phase #%d\n", cpt);
        printf("=========================\n\n");

        //Initialisation des variables
        t_move random_moves_pool[RANDOM_POOL_SIZE];
        generate_random_moves_pool(random_moves_pool, RANDOM_POOL_SIZE, weighted_moves, NUM_MOVES);
        print_moves_pool(random_moves_pool, RANDOM_POOL_SIZE);
        int pool_size = RANDOM_POOL_SIZE;

        // Construction de l'arbre
        p_nnode root = buildTree(map, loc.pos.x, loc.pos.y, 5, max_moves, random_moves_pool, RANDOM_POOL_SIZE, reg);

        // Trouver le chemin avec le coût minimum
        p_nnode min = searchleaf(root, root);
        if (searchmin(root,root)->value == 0)
        {
            min = searchmin(root,root);
        }

        // Recherche du chemin
        p_nnode chemin[100];
        int index = 0;

        // Dans la fonction bot_function(), après la recherche du chemin
        if (findpath(root, min, chemin, &index))
        {
            // Afficher le chemin trouvé
            //print_path(chemin, index);
        }
        else
        {
            break;
        }

        // Exécution des mouvements du chemin
        for (int i = 1; i < index; i++)
        {
            t_move move = chemin[i]->movement;

            // Vérifier si le mouvement est encore dans le pool
            int valid_move = 0;
            for (int j = 0; j < RANDOM_POOL_SIZE; j++)
            {
                if (random_moves_pool[j] == move)
                {
                    valid_move = 1;
                    break;
                }
            }

            if (valid_move)
            {
                // Exécuter le mouvement et mettre à jour l'état du robot
                move_robot_and_print(&loc, move, map, &reg);

                // Retirer le mouvement du pool
                remove_move_from_pool(random_moves_pool, &pool_size, move);

                // Vérifier la fin de la phase
                if (map.costs[loc.pos.y][loc.pos.x] == 0)
                {
                    printf("Target or base reached in phase #%d: (%d, %d)\n", cpt, loc.pos.x, loc.pos.y);
                    return;
                }
            }
            else
            {
                printf("Invalid move: %s not available in pool.\n", getMoveAsString(move));
            }
        }

        // Mise à jour de `max_moves` pour le terrain "Reg"
        if (reg == 1)
        {
            max_moves = 4;
            reg = 0;
        }
        else
        {
            max_moves = 5;  // Réinitialisation si aucun "Reg"
        }

        // Passage à la phase suivante
        cpt++;
    }

    printf("Final position: (%d, %d), orientation: %d\n", loc.pos.x, loc.pos.y, loc.ori);
}
