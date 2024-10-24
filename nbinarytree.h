//
// Created by ayuna on 24/10/2024.
//

#ifndef UNTITLED1_NBINARYTREE_H
#define UNTITLED1_NBINARYTREE_H


struct s_cell
{
    struct s_cell *next;
    struct s_nnode *node;
};

typedef struct s_cell t_cell, *p_cell;


typedef struct s_nnode
{
    int value ;
    p_cell L ;
} t_nnode ;



typedef struct ht_list
{
    t_cell* head ;
    t_cell* tail ;
}t_ht_list;


typedef struct tree
{
    t_nnode* head ;
}t_tree;

t_nnode create_node(int, int);
p_cell create_empty_cell(int);
t_tree create_empty_tree();
void add_node(t_tree, int, int);
void display_tree(t_tree);


#endif //UNTITLED1_NBINARYTREE_H
