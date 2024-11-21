#include <stdlib.h>
#include <stdio.h>
#include "nbinarytree.h"
#include "node.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * AFFICHAGE D'UN ARBRE
------------------------------------------------------------------------------------------------------------------------------------------------- */

void display_tree_visual(p_nnode node, int depth)
{
    //Si le noeud racine est vide, on affiche rien, car l'arbre est vide
    if (node == NULL)
    {
        return;
    }

    // Affichage du nœud actuel
    for (int i = 0; i < depth; i++)
    {
        printf("    ");  // Indentation pour les sous-niveaux
    }
    //Affiche la valeur du noeud
    printf("[%03d]", node->value);
    //Affiche le mouvement du noeud
    printf("%s\n", getMoveAsString(node->movement));


    // Affichage des enfants s'ils existent
    if (node->child_count > 0)
    {
        //Boucle utilisant le nombre d'enfants
        for (int i = 0; i < node->child_count; i++)
        {
            for (int j = 0; j < depth; j++)
            {
                printf("    ");  // Indentation pour les sous-niveaux
            }
        }
        printf("\n");

        // Affichage des flèches vers les enfants
        for (int i = 0; i < node->child_count; i++)
        {
            for (int j = 0; j < depth + 1; j++)
            {
                printf("    ");
            }
            printf("|\n");

            // Affichage des enfants eux-mêmes
            display_tree_visual(node->children[i], depth + 1);
        }
    }
}

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS CHERCHANT LE NOEUD MINIMUM
------------------------------------------------------------------------------------------------------------------------------------------------- */

p_nnode searchmin(p_nnode node, p_nnode min)
{
    //Si il n'y a pas d'arbre, retourne NULL
    if (node == NULL)
    {
        return min;
    }

    //Si la valeur du noeud est inférieure à celle du minimum, donner le noeud à min
    if (node->value < min->value)
    {
        min = node;
    }

    //Pour tous les enfants, on descend le long de l'arbre
    for (int i = 0; i < node->child_count; i++)
    {
        min = searchmin(node->children[i], min);
    }
    return min;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS CHERCHANT LA FEUILLE MINIMALE
------------------------------------------------------------------------------------------------------------------------------------------------- */

p_nnode searchleaf(p_nnode node, p_nnode min)
{
    //Si le noeud est nul, on retourne le min
    if (node == NULL)
    {
        return min;
    }

    //Si la valeur dépasse 999 (si c'est une crevasse), on retourne min
    if (node->value > 999)
    {
        return min;
    }

    // On vérifie si le noeud actuel est une feuille
    if (node->child_count == 0)
    {
        if (min == NULL || node->value < min->value)
        {
            min = node;
        }
    }

    // On vérifie tous les enfants
    for (int i = 0; i < node->child_count; i++)
    {
        min = searchleaf(node->children[i], min);
    }

    return min;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS CHERCHAT LE CHEMIN VERS UN NOEUD
------------------------------------------------------------------------------------------------------------------------------------------------- */

int findpath(p_nnode node, p_nnode target, p_nnode chemin[], int* index)
{
    if (node == NULL)
    {
        return 0;
    }

    // Ajouter le nœud actuel au chemin
    chemin[(*index)++] = node;

    // Vérifier si le nœud actuel est le nœud cible
    if (node == target)
    {
        return 1;  // Trouvé !
    }

    // Recherche récursive dans les enfants
    for (int i = 0; i < node->child_count; i++)
    {
        if (findpath(node->children[i], target, chemin, index))
        {
            return 1;  // Trouvé un chemin via un enfant
        }
    }

    // Si le chemin n'est pas trouvé, retour arrière
    (*index)--;
    return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------
 * FONCTIONS CHERCHANT UN NOEUD DANS UN ARBRE A PARTIR D'UNE VALEUR
------------------------------------------------------------------------------------------------------------------------------------------------- */

p_nnode find_node(p_nnode node, int val)
{
    if (node == NULL)
    {
        return NULL;
    }

    //Retourne le noeud si la valeur est trouvée
    if (node->value == val)
    {
        return node;
    }

    for (int i = 0; i < node->child_count; i++)
    {
        p_nnode found = find_node(node->children[i], val);
        if (found != NULL)
        {
            return found;
        }
    }
    return NULL;
}


