//
// Created by ayuna on 14/11/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H
#include "moves.h"


/*------------------------------------------------------------------------------------------------------------------------------------------------
 * STRUCTURE
------------------------------------------------------------------------------------------------------------------------------------------------- */

typedef struct nnode {
    int value; //Valeur
    struct nnode** children;  // Pointeur vers les enfants
    int child_count;          // Nombre des enfants
    int x;      // Coordonnée x
    int y;      // Coordonnée y
    t_move movement; //Le mouvement permettant d'atteindre le noeud actuel
    t_orientation ori; //Orientation du robot quand il atteint ce noeud
} t_nnode, *p_nnode;

/***
 * @brief
 * @param
 * @return
 */

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS
------------------------------------------------------------------------------------------------------------------------------------------------- */

// Créer un noeud
p_nnode createNode(int, int, int, t_move);

//Affiche les noeuds
void display_node(p_nnode);

//Ajoute un enfant à un noeud
void add_child(p_nnode parent, p_nnode val);

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------- */


#endif //UNTITLED1_NODE_H
