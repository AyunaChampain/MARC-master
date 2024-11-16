//
// Created by ayuna on 14/11/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "node.h"


p_nnode createNode(int val)
{
    p_nnode nouv = (p_nnode)malloc(sizeof(t_nnode));
    nouv->value = val;
    nouv->children = NULL;   // No children initially
    nouv->child_count = 0;   // Zero children
    return nouv;
}

void display_node(p_nnode node) {
    if (node != NULL) {
        // Display the current node's value
        printf("%d ", node->value);

        // Recursively display all children
        for (int i = 0; i < node->child_count; i++) {
            display_node(node->children[i]);
        }
    }
}


void add_child(p_nnode parent, int val) {
    if (parent == NULL) return;

    // Allocate memory for the new child array
    parent->children = (p_nnode*)realloc(parent->children, (parent->child_count + 1) * sizeof(p_nnode));
    parent->children[parent->child_count] = createNode(val);
    parent->child_count++;
}
