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
    p_nnode curr ;
    curr = T->root ;
    if (T->root != NULL)
    {
        printf("%d", T->root->value);
        while(curr->right != NULL)
        {
            curr=curr->right;
            printf("%d", T->root->value);
        }
    }
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
