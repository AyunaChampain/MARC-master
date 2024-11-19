//
// Created by ayuna on 16/11/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "bot.h"
#include "nbinarytree.h"
#include "map.h"
#include "node.h"
#include "loc.h"
#include "moves.h"
#include "stack.h"
#include "queue.h"

int isValidPosition(int x, int y, t_map map)
{
    return x >= 0 && x < map.x_max && y >= 0 && y < map.y_max;  // Assurez-vous que la position est dans les limites
}

void addNeighborsAsChildrenRecursive(p_nnode node, t_position pos, t_map map, int depth, t_move move)
{
    if (depth <= 0) {
        return;  // Arrêter la récursion si on atteint la profondeur limite
    }

    // Définir les déplacements possibles
    t_position moves[] = {
            {pos.x + 1, pos.y}, // Mouvement vers la droite
            {pos.x - 1, pos.y}, // Mouvement vers la gauche
            {pos.x, pos.y + 1}, // Mouvement vers le bas
            {pos.x, pos.y - 1}  // Mouvement vers le haut
    };

    // Essayer chaque déplacement
    for (int i = 0; i < 4; i++) {
        int new_x = moves[i].x;
        int new_y = moves[i].y;

        // Vérifier si la position est valide avant de l'ajouter
        if (isValidPosition(new_x, new_y, map)) {
            int cost = map.costs[new_y][new_x];  // Coût du voisin valide
            t_move new_move = move;

            // Créer un nœud pour le voisin et l'ajouter en tant qu'enfant
            p_nnode child = createNode(cost, new_x, new_y, new_move);
            add_child(node, child);  // Ajouter le nœud enfant au nœud actuel

            // Appel récursif pour ajouter les voisins du voisin
            addNeighborsAsChildrenRecursive(child, moves[i], map, depth - 1, new_move);
        }
    }
}

p_nnode buildTree(t_map map, int posx, int posy, int depth) {
    // Créer la racine de l'arbre
    t_position pos = {posx, posy};
    int root_cost = map.costs[posy][posx];
    p_nnode root = createNode(root_cost, posx, posy, F_10);  // F_10 initialisé comme mouvement de départ

    // Ajouter les voisins à la racine
    addNeighborsAsChildrenRecursive(root, pos, map, depth, F_10);

    return root;
}




void move_robot_and_print(t_localisation *loc, t_move movement) {
    // Effectuer le mouvement
    *loc = move(*loc, movement);

    // Afficher le nom du mouvement et la nouvelle position
    printf("Moved to position (%d, %d) using move: %s\n", loc->pos.x, loc->pos.y, getMoveAsString(movement));
}


void bot_function(struct s_map map, int arx, int ary)
{
    int posx = 4;  // Starting x position
    int posy = 6;  // Starting y position
    int cpt = 1;

    t_localisation loc = loc_init(posx, posy, NORTH);  // Initialize the bot's position and orientation (assuming 'NORTH' is the initial orientation)

    p_nnode chemin_complet[1000];  // Array to store the complete path
    int chemin_complet_index = 0;

    while (posx != arx || posy != ary)
    {
        printf("%dth phase\n", cpt);
        p_nnode root = buildTree(map, posx, posy, 5);
        display_tree_visual(root, 0);

        p_nnode min = searchleaf(root, root);  // Find the minimum cost leaf node
        printf("Minimum value in tree: %d\n", min->value);

        p_nnode chemin[100];  // Array to store the path
        int index = 0;        // Path index

        if (findpath(root, min, chemin, &index)) {
            printf("Path from root to min: ");
            for (int i = 0; i < index; i++) {
                printf("[%d] ", chemin[i]->value);  // Print path values (these are assumed to be move types)
            }
            printf("\n");
        }
        else {
            printf("No path found to min.\n");
            break;
        }

        // Store the path from the root to the destination
        int i;
        if (chemin_complet_index > 0) {
            i = 1;  // Skip the first element (if already there)
        } else {
            i = 0;  // Start from the first element
        }
        for (i; i < index; i++) {
            chemin_complet[chemin_complet_index++] = chemin[i];
            posx = chemin[i]->x;
            posy = chemin[i]->y;
        }

        // Execute the moves along the path
        for (int i = 0; i < chemin_complet_index; i++) {
            t_move move = chemin_complet[i]->value;  // Assuming 'value' contains the move type (e.g., F_10, T_LEFT, etc.)

            // Check if the move is a turn or a translation (forward/backward)
            if (move == T_LEFT || move == T_RIGHT || move == U_TURN) {
                printf("Turn: %s\n", getMoveAsString(move));  // Print the turn type
                updateLocalisation(&loc, move);  // Update orientation for turn
            } else {
                printf("Move: %s\n", getMoveAsString(move));  // Print the forward/backward move
                updateLocalisation(&loc, move);  // Update position and orientation for forward/backward move
            }

            // After moving, print the new position and orientation
            printf("Moved to position (%d, %d) with orientation %d\n", loc.pos.x, loc.pos.y, loc.ori);
        }
        cpt++;
    }
}


