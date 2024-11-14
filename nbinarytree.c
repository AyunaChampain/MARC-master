//
// Created by ayuna on 24/10/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include "nbinarytree.h"

p_cell create_empty_cell()
{
    p_cell c ;
    c->next = NULL ;
}

t_nnode create_node(int nb, int val)
{
    t_nnode racine ;
    p_cell new_cell;
    p_cell current ;
    int i ;

    new_cell = create_empty_cell();

    racine.value = val ;
    racine.L = new_cell ;
    current = new_cell ;
    for (i = 1; i < nb; i++)
    {
        current-> next = new_cell ;
        current->node = NULL ;
        current = current -> next ;
    }
    current->next = NULL;
    current->node = NULL ;

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
    printf("%d->", T.head->value);
    //current = T.head->L ;
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