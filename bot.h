#ifndef BOT_H
#define BOT_H

#include "map.h"
#include "node.h"
#include "loc.h"
#include "moves.h"
#include "nbinarytree.h"


/*------------------------------------------------------------------------------------------------------------------------------------------------
 * STRUCTURE
------------------------------------------------------------------------------------------------------------------------------------------------- */

//Structure liant un mouvement à une probabilité (sa probabilité d'être choisie)
typedef struct
{
    t_move move;
    double probability;
} t_weighted_move;

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * CREATION DE L'ARBRE
------------------------------------------------------------------------------------------------------------------------------------------------- */

//Créer l'arbre de mouvements
p_nnode buildTree(t_map map, int posx, int posy, int depth, int max_moves, t_move pool[], int pool_size, int reg) ;

//Permet d'ajouter les mouvements possibles en temps qu'enfants d'un noeud
void addNeighborsAsChildrenRecursive(p_nnode node, t_localisation loc, t_map map, int depth, int max_moves, t_move pool[], int pool_size, int reg) ;

//Fontion vérifiant la validité d'une position
int isValidPosition(int x, int y, t_map map);

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS PRINCIPALES
------------------------------------------------------------------------------------------------------------------------------------------------- */

//Fonction principale
void bot_function(struct s_map map, int, int);

//Permet le déplacement du robot
void move_robot_and_print(t_localisation *loc, t_move movement, t_map map, int* reg);

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS LIEES AU POOL
------------------------------------------------------------------------------------------------------------------------------------------------- */

//Retire un mouvement d'un pool
void remove_move_from_pool(t_move pool[], int *pool_size, t_move move);

//Fonction choisissant un mouvement aléatoire
t_move choose_random_move(t_weighted_move moves[], int size);

//Créer un pool de mouvements
void generate_random_moves_pool(t_move pool[], int pool_size, t_weighted_move moves[], int num_moves);

//Affiche le pool
void print_moves_pool(t_move pool[], int pool_size);

//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------

#endif // BOT_H
