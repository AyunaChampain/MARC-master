//
// Created by ayuna on 14/11/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "node.h"


p_nnode createNode(int val)
{
    p_nnode nouv;

    nouv = (p_nnode)malloc(sizeof(t_nnode));
    nouv->value = val;
    nouv->left = nouv->right = NULL;

    return nouv;
}
