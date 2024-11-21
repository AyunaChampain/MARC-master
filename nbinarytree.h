//
// Created by ayuna on 24/10/2024.
//

#ifndef UNTITLED1_NBINARYTREE_H
#define UNTITLED1_NBINARYTREE_H

#include "node.h"
#include "nbinarytree.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * STRUCTURE
------------------------------------------------------------------------------------------------------------------------------------------------- */

typedef struct ntree
{
    p_nnode root;
} t_tree, *p_tree;

/*------------------------------------------------------------------------------------------------------------------------------------------------
* AFFICHAGE D'ARBRE
------------------------------------------------------------------------------------------------------------------------------------------------- */

void display_tree_visual(p_nnode node, int depth);

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS GERANT LE MINIMUM D'UN ARBRE ET LE CHEMIN POUR L'ATTEINDRE
------------------------------------------------------------------------------------------------------------------------------------------------- */

p_nnode searchmin(p_nnode, p_nnode); //Fonction qui permet de retrouver la feuille de l'arbre avec la plus petite valeur
p_nnode searchleaf(p_nnode, p_nnode);
int findpath(p_nnode, p_nnode, p_nnode*, int*);
p_nnode find_node(p_nnode, int);

#endif
