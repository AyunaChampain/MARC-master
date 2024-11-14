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

void display_tree(p_tree T)
{
    int check = 0 ;
    t_nnode* current ;
    printf("%d->", T->root->value);
    //current = T.head->L ;
    printf("Flag");
    //while (current->next != NULL)
    {
        printf("%d|", current->right->value);
        if (current->right != NULL)
        {
            check = 1 ;
        }
        current = current -> right ;
    }
}

void add_node(p_tree T, int val)
{
    p_nnode new ;
    p_nnode curr ;
    new = createNode(val);
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
