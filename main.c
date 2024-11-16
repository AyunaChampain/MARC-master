 #include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "nbinarytree.h"
#include "node.h"

//Github test !

 int main()
 {
     p_tree Tree = (p_tree)malloc(sizeof(t_tree));
     Tree->root = createNode(10);

     add_child(Tree->root, 20);
     add_child(Tree->root, 30);
     add_child(Tree->root, 40);
     add_child(Tree->root, 50);
     add_child(Tree->root, 60);

     p_nnode node20 = find_node(Tree->root, 20);
     add_child(node20, 25);
     add_child(node20, 28);

     display_tree_visual(Tree->root, 0);

     p_nnode min = searchmin(Tree->root, Tree->root);
     printf("Minimum value in tree: %d\n", min->value);

     return 0;
 }
