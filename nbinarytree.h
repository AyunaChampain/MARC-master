//
// Created by ayuna on 24/10/2024.
//

#ifndef UNTITLED1_NBINARYTREE_H
#define UNTITLED1_NBINARYTREE_H



struct s_cell
{
    int value;
    struct s_cell *next;
};

typedef struct s_cell t_cell, *p_cell;

typedef struct ht_list
{
    t_cell* head ;
    t_cell* tail ;
}t_ht_list;

typedef struct s_nnode
{
    int value ;
    p_cell L ;
} t_nnode ;

t_nnode create_node(int, int);
p_cell create_empty_cell(int);


#endif //UNTITLED1_NBINARYTREE_H
