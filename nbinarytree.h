//
// Created by ayuna on 24/10/2024.
//

#ifndef UNTITLED1_NBINARYTREE_H
#define UNTITLED1_NBINARYTREE_H

#include "node.h"

typedef struct s_tree
{
    p_node root;
} t_tree, *p_tree;

void BFVisit(t_tree);

// pour utiliser l'affichage d'arbres
#define LINE_SIZE 1024
#define MAX_NB_LINES 100

int _print_t(p_node, int , int , int, char s[MAX_NB_LINES][LINE_SIZE]);
void print_t(p_node);
void displayTree(t_tree);

#endif
