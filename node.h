//
// Created by ayuna on 14/11/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

typedef struct nnode {
    int value;
    struct nnode** children;  // Dynamic array of pointers to child nodes
    int child_count;          // Number of children
    int x;      // Coordonnée x
    int y;
} t_nnode, *p_nnode;



/***
 * @brief
 * @param
 * @return
 */
p_nnode createNode(int, int, int);
void display_node(p_nnode);
void minnode(p_nnode, int);
void add_depth(p_nnode, int);
void add_child(p_nnode parent, p_nnode val);

#endif //UNTITLED1_NODE_H
