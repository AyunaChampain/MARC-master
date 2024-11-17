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
            //printf("Adding child node with cost: %d at position (%d, %d)\n", neighbor_cost, neighbor.x, neighbor.y);
            p_nnode child = createNode(neighbor_cost, neighbor.x, neighbor.y);

            // Ajouter ce nœud comme enfant du parent
            add_child(parent, child);

            // Appeler récursivement pour ajouter les voisins de cet enfant
            addNeighborsAsChildrenRecursive(child, neighbor, map, depth - 1);
        }
    }
}

p_nnode buildTree(t_map map, int posx, int posy, int depth) {
    // Créer la racine de l'arbre
    t_position pos = {posx, posy};
    int root_cost = map.costs[posy][posx];
    p_nnode root = createNode(root_cost, posx, posy);

    // Ajouter les voisins à la racine
    addNeighborsAsChildrenRecursive(root, pos, map, depth);

    return root ;
}


void bot_function(struct s_map map, int arx, int ary)
{
    int posx = 4;
    int posy = 6;
    int cpt = 1;

    p_nnode chemin_complet[1000]; // Tableau pour stocker le chemin complet
    int chemin_complet_index = 0;

    while (posx != arx || posy != ary)
    {
        printf("%dth phase\n", cpt);
        p_nnode root = buildTree(map, posx, posy, 5);
        //display_tree_visual(root, 0);

        p_nnode min = searchleaf(root, root);
        printf("Minimum value in tree: %d\n", min->value);

        p_nnode chemin[100];  // Tableau pour stocker le chemin
        int index = 0;        // Index pour le chemin

        if (findpath(root, min, chemin, &index)) {
            printf("Path from root to min: ");
            for (int i = 0; i < index; i++) {
                printf("[%d] ", chemin[i]->value);
            }
            printf("\n");
        }
        else
        {
            printf("No path found to min.\n");
            break;
        }

        int i ;
        if (chemin_complet_index > 0)
        {
            i = 1 ;
        }
        else
        {
            i = 0 ;
        }
        for (i; i < index; i++) {
            chemin_complet[chemin_complet_index++] = chemin[i];
            // Mettre à jour la position
            posx = chemin[i]->x;
            posy = chemin[i]->y;
        }

        cpt++;
    }

    for (int j = 0; j < chemin_complet_index; j++) {
        printf("[%d] ", chemin_complet[j]->value);
    }
}
