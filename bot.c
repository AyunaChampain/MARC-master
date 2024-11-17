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


void addNeighborsAsChildren(p_nnode parent, t_position pos, t_map map) {
    t_position directions[4] = {
            LEFT(pos), RIGHT(pos), UP(pos), DOWN(pos)
    };

    // Boucle sur les 4 voisins (gauche, droite, haut, bas)
    for (int i = 0; i < 4; i++) {
        t_position neighbor = directions[i];

        // Vérifier que la case voisine est valide
        if (isValidLocalisation(neighbor, map.x_max, map.y_max)) {
            // Créer un nœud pour la case voisine et récupérer son coût
            int neighbor_cost = map.costs[neighbor.y][neighbor.x];
            printf("Adding child node with cost: %d at position (%d, %d)\n", neighbor_cost, neighbor.x, neighbor.y);
            p_nnode child = createNode(neighbor_cost);

            // Ajouter le nœud enfant au parent
            add_child(parent, child);
        }
    }
}

void addNeighborsAsChildrenRecursive(p_nnode parent, t_position pos, t_map map, int depth) {
    if (depth == 0) return;  // Si la profondeur est 0, arrêtez la récursion

    // Vérifier les voisins (gauche, droite, haut, bas)
    t_position directions[4] = {
            LEFT(pos), RIGHT(pos), UP(pos), DOWN(pos)
    };

    // Boucle sur les 4 voisins (gauche, droite, haut, bas)
    for (int i = 0; i < 4; i++) {
        t_position neighbor = directions[i];

        // Vérifier que la case voisine est valide
        if (isValidLocalisation(neighbor, map.x_max, map.y_max)) {
            // Créer un nœud pour la case voisine et récupérer son coût
            int neighbor_cost = map.costs[neighbor.y][neighbor.x];
            printf("Adding child node with cost: %d at position (%d, %d)\n", neighbor_cost, neighbor.x, neighbor.y);
            p_nnode child = createNode(neighbor_cost);

            // Ajouter ce nœud comme enfant du parent
            add_child(parent, child);

            // Appeler récursivement pour ajouter les voisins de cet enfant
            addNeighborsAsChildrenRecursive(child, neighbor, map, depth - 1);
        }
    }
}

void buildTree(t_map map, int posx, int posy, int depth) {
    // Créer la racine de l'arbre
    t_position pos = {posx, posy};
    int root_cost = map.costs[posy][posx];
    p_nnode root = createNode(root_cost);

    // Ajouter les voisins à la racine
    addNeighborsAsChildrenRecursive(root, pos, map, depth);

    // Affichage de l'arbre à la fin
    display_tree_visual(root, 0);
}