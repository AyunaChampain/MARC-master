//
// Created by ayuna on 24/10/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include "nbinarytree.h"

p_cell create_empty_cell(int val)
{
    p_cell c ;
    c->next = NULL ;
}

t_nnode create_node(int nb, int val)
{
    t_nnode racine ;
    int* T[nb];
    p_cell new_cell;

    new_cell = create_empty_cell(0);

    racine.value = val ;
    racine.L = new_cell ;

    return racine ;
}

t_tree create_empty_tree()
{
    t_tree T ;

    T.head = NULL ;
    return T ;
}

void add_node(t_tree T, int val, int nb)
{
    t_nnode new ;
    t_cell* current ;

    new = create_node(nb,val);
    if (T.head == NULL)
    {
        T.head = &new ;
        return ;
    }

    current = T.head->L ;
    while (current != NULL)
    {
        current->node = &new ;
        current = current->next ;
    }
}

void display_tree(t_tree T)
{
    int check = 0 ;
    t_cell* current ;
    printf("%d->", T.head);
    current = T.head->L ;
    printf("Flag");
    //while (current->next != NULL)
    {
        printf("%d|", current->node->value);
        if (current->node->L->node != NULL)
        {
            check = 1 ;
        }
        current = current -> next ;
    }
}