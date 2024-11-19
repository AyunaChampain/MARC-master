//
// Created by ayuna on 14/11/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "node.h"


p_nnode createNode(int val, int x, int y, t_move mov)
{
    p_nnode nouv = (p_nnode)malloc(sizeof(t_nnode));
    if (nouv == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour un nœud\n");
        exit(1);  // Si l'allocation échoue, on arrête le programme
    }
    nouv->value = val;
    nouv->children = NULL;   // No children initially
    nouv->child_count = 0;   // Zero children
    nouv->x = x;
    nouv->y = y;
    nouv->movement = mov;
    return nouv;
}

void display_node(p_nnode node) {
    if (node == NULL) {
        printf("[NULL]");
        return;
    }
    printf("[%03d]", node->value); // Affiche la valeur du nœud avec un format à 3 chiffres
}

/*void display_node(p_nnode node) {
    if (node != NULL) {
        // Display the current node's value
        printf("%d ", node->value);

        // Recursively display all children
        for (int i = 0; i < node->child_count; i++) {
            display_node(node->children[i]);
        }
    }
}*/


void add_child(p_nnode parent, p_nnode child) {
    if (parent->children == NULL) {
        parent->children = (p_nnode)malloc(sizeof(p_nnode));
        parent->children[0] = child;  // Ajouter le premier enfant
        parent->child_count = 1;// Initialiser le nombre d'enfants
    }
    else
    {
        parent->children = (p_nnode *)realloc(parent->children, sizeof(p_nnode) * (parent->child_count + 1));
        parent->children[parent->child_count] = child;
        parent->child_count++;  // Incrémenter le nombre d'enfants
    }
}
