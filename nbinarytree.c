//
// Created by ayuna on 24/10/2024.
//

#include <stdlib.h>
#include "nbinarytree.h"

p_cell create_empty_cell(int val)
{
    p_cell c ;
    c->value = val ;
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