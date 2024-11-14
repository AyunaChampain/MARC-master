//
// Created by ayuna on 24/10/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include "nbinarytree.h"
#include "node.h"

p_tree create_empty_tree()
{
    p_tree T = (p_tree)malloc(sizeof(t_tree));
    T->root = NULL;
    return T;
}


void display_tree(p_tree T) {
    if (T == NULL || T->root == NULL) {
        return; // Si l'arbre est vide, on n'affiche rien
    }
    display_node(T->root);
}

void add_node(p_tree T, int val)
{
    p_nnode new ;
    p_nnode curr ;

    p_nnode parent = NULL;
    new = createNode(val);
    curr = T->root ;
    if (T->root == NULL)
    {
        T-> root = new ;
    }
    else
    {
        while (curr != NULL)
        {
            parent = curr;
            if (val < curr->value) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        if (val < parent->value) {
            parent->left = new;
        } else {
            parent->right = new;
        }
    }
}


void display_tree_visual(p_nnode node, int depth) {
    if (node == NULL) {
        return;
    }
    display_tree_visual(node->right, depth + 1);  // Affiche le sous-arbre droit en premier pour décaler à droite

    // Indentation pour chaque niveau
    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }
    printf("%d\n", node->value);  // Affiche la valeur du nœud

    display_tree_visual(node->left, depth + 1);   // Affiche le sous-arbre gauche
}

// Appel de la fonction avec la racine
void display_tree_structure(p_tree T) {
    if (T == NULL || T->root == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }
    display_tree_visual(T->root, 0);  // Démarre l'affichage à la racine avec une profondeur de 0
}
