#include <stdlib.h>
#include <stdio.h>
#include "node.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS CREANT UN NOEUD
------------------------------------------------------------------------------------------------------------------------------------------------- */

p_nnode createNode(int val, int x, int y, t_move mov)
{
    //Allocation de mémoire
    p_nnode nouv = (p_nnode)malloc(sizeof(t_nnode)); //Alloue la mémoire nécessaire
    if (nouv == NULL)
    {
        printf("Erreur d'allocation mémoire pour un nœud\n");
        exit(1);  // Si l'allocation échoue, on arrête le programme
    }

    //Initialise les différentes valeurs du noeud
    nouv->value = val; //Sa valeur
    nouv->children = NULL;   //Pas d'enfants
    nouv->child_count = 0;   //Zero
    nouv->x = x; //position x
    nouv->y = y; //position y
    nouv->movement = mov; //Le mouvement nécessaire pour accéder au noeud

    return nouv;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * AJOUTE UN ENFANT A UN NOEUD
------------------------------------------------------------------------------------------------------------------------------------------------- */

void add_child(p_nnode parent, p_nnode child) {
    //Si il n'y a aucun enfant...
    if (parent->children == NULL) {
        parent->children = (p_nnode)malloc(sizeof(p_nnode)); //Allocation mémoire
        parent->children[0] = child;  // Ajoute le premier enfant
        parent->child_count = 1; // Initialise le nombre d'enfants
    }
    //Sinon
    else
    {
        parent->children = (p_nnode *)realloc(parent->children, sizeof(p_nnode) * (parent->child_count + 1)); //Allocation mémoire
        parent->children[parent->child_count] = child; //Ajoute l'enfant
        parent->child_count++;  // Incrémente le nombre d'enfants
    }
}