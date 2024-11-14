//
// Created by ayuna on 24/10/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include "nbinarytree.h"

p_tree create_empty_tree()
{
    t_nnode c ;
    c.right = NULL ;
    c.left = NULL ;
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
    new = createNode(val);
    curr = T->root ;
    if (T->root == NULL)
    {
        T-> root = new ;
    }
    else
    {
        while (curr->right != NULL)
        {
            curr=curr->right ;
        }
        curr = new ;
    }
}
