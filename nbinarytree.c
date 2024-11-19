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




void display_tree_visual(p_nnode node, int depth) {
    if (node == NULL) {
        return;
    }

    // Affichage du nœud actuel
    for (int i = 0; i < depth; i++) {
        printf("    ");  // Indentation pour les sous-niveaux
    }
    printf("[%03d]", node->value);
    printf("%s\n", getMoveAsString(node->movement));


    // Affichage des enfants s'ils existent
    if (node->child_count > 0) {
        for (int i = 0; i < node->child_count; i++) {
            for (int j = 0; j < depth; j++) {
                printf("    ");  // Indentation pour les sous-niveaux
            }
        }
        printf("\n");

        // Affichage des flèches vers les enfants
        for (int i = 0; i < node->child_count; i++) {
            for (int j = 0; j < depth + 1; j++) {
                printf("    ");
            }
            printf("|\n");

            // Affichage des enfants eux-mêmes
            display_tree_visual(node->children[i], depth + 1);
        }
    }
}



// Appel de la fonction avec la racine
void display_tree_structure(p_tree T) {
    if (T == NULL || T->root == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }
    display_tree_visual(T->root, 0);  // Démarre l'affichage à la racine avec une profondeur de 0
}


p_nnode searchmin(p_nnode node, p_nnode min) {
    if (node == NULL) return min;
    if (node->value < min->value) min = node;

    for (int i = 0; i < node->child_count; i++) {
        min = searchmin(node->children[i], min);
    }
    return min;
}



p_nnode searchleaf(p_nnode node, p_nnode min) {
    if (node == NULL)
        return min;

    if (node->value > 999) {
        return min;
    }

    // Check if the current node is a leaf
    if (node->child_count == 0) {
        if (min == NULL || node->value < min->value) {
            min = node;
        }
    }

    // Recursively check all children
    for (int i = 0; i < node->child_count; i++) {
        min = searchleaf(node->children[i], min);
    }

    return min;
}


int findpath(p_nnode node, p_nnode target, p_nnode chemin[], int* index) {
    if (node == NULL) {
        return 0;
    }

    // Ajouter le nœud actuel au chemin
    chemin[(*index)++] = node;

    // Vérifier si le nœud actuel est le nœud cible
    if (node == target) {
        return 1;  // Trouvé !
    }

    // Recherche récursive dans les enfants
    for (int i = 0; i < node->child_count; i++) {
        if (findpath(node->children[i], target, chemin, index)) {
            return 1;  // Trouvé un chemin via un enfant
        }
    }

    // Si le chemin n'est pas trouvé, retour arrière
    (*index)--;
    return 0;
}


p_nnode find_node(p_nnode node, int val) {
    if (node == NULL) return NULL;
    if (node->value == val) return node;

    for (int i = 0; i < node->child_count; i++) {
        p_nnode found = find_node(node->children[i], val);
        if (found != NULL) return found;
    }
    return NULL;
}


