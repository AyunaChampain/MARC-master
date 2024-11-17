 #include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "nbinarytree.h"
#include "node.h"
#include "node.h"

//Github test !

 int main()
 {
     t_map map;

     // The following preprocessor directive checks if the code is being compiled on a Windows system.
     // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
     // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
     map = createMapFromFile("..\\maps\\example1.map");
#else
     map = createMapFromFile("../maps/example1.map");
#endif

     printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
     for (int i = 0; i < map.y_max; i++)
     {
         for (int j = 0; j < map.x_max; j++)
         {
             printf("%d ", map.soils[i][j]);
         }
         printf("\n");
     }
     // printf the costs, aligned left 5 digits
     for (int i = 0; i < map.y_max; i++)
     {
         for (int j = 0; j < map.x_max; j++)
         {
             printf("%-5d ", map.costs[i][j]);
         }
         printf("\n");
     }
     displayMap(map);



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
