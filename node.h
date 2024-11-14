//
// Created by ayuna on 14/11/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

struct s_nnode
{
    int value;
    struct s_nnode   *left, *right;
    int depth;
};

typedef struct s_nnode t_nnode, *p_nnode;

/***
 * @brief
 * @param
 * @return
 */
p_nnode createNode(int);

#endif //UNTITLED1_NODE_H
