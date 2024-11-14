//
// Created by ayuna on 24/10/2024.
//

#ifndef UNTITLED1_NBINARYTREE_H
#define UNTITLED1_NBINARYTREE_H

#include "node.h"
#include "nbinarytree.h"

typedef struct s_tree
{
    p_nnode root;
} t_tree, *p_tree;

void BFVisit(t_tree);

// pour utiliser l'affichage d'arbres
#define LINE_SIZE 1024
#define MAX_NB_LINES 100

int _print_t(p_nnode, int , int , int, char s[MAX_NB_LINES][LINE_SIZE]);
void print_t(p_nnode);
void displayTree(t_tree);
p_tree create_empty_tree() ;
void add_node(p_tree, int);
void display_tree(p_tree);
void BFVisit(t_tree);

void display_tree_structure(p_tree T);
void display_tree_visual(p_nnode node, int depth);

p_nnode searchmin(p_tree); //Fonction qui permet de retrouver la feuille de l'arbre avec la plus petite valeur
p_nnode searchleaf(p_nnode, p_nnode);

#endif
