//
// Created by ayuna on 14/11/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "node.h"


p_nnode createNode(int val)
{
    p_nnode nouv;

    nouv = (p_nnode)malloc(sizeof(t_nnode));
    nouv->value = val;
    nouv->left = nouv->right = NULL;

    return nouv;
}

void display_node(p_nnode node) {
    if (node != NULL)
    {
        display_node(node->left);      // Parcourir le sous-arbre gauche
        printf("%d ", node->value);    // Afficher la valeur du nœud actuel
        display_node(node->right);     // Parcourir le sous-arbre droit
    }
}

