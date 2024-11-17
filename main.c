 #include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "nbinarytree.h"
#include "node.h"
#include "node.h"
#include "loc.h"
#include "bot.h"

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
     //add_child(Tree->root, 20);
     //add_child(Tree->root, 30);
     p_nnode node20 = find_node(Tree->root, 20);
     //add_child(node20, 25);
     //add_child(node20, 28);
     display_tree_visual(Tree->root, 0);
     p_nnode min = searchmin(Tree->root, Tree->root);
     printf("Minimum value in tree: %d\n", min->value);


     int posx = 4;
     int posy = 6;

     if (!(posx >= 0 && posx < map.x_max && posy >= 0 && posy < map.y_max))
     {
        printf("Error: Invalid position (%d, %d) on the map\n", posx, posy);
         exit(1);
     }

     /*p_tree pos = create_empty_tree();
     p_nnode depart = createNode(map.costs[posy][posx]);
     pos->root = depart ;
     display_tree_visual(pos->root,0);*/


     t_position start_pos = {1, 1};

     p_tree pos = create_empty_tree();
     p_nnode root = createNode(map.costs[start_pos.y][start_pos.x]);
     pos->root = root;

     // Ajouter les voisins comme enfants du nœud racine
     addNeighborsAsChildren(root, start_pos, map);


     display_tree_visual(pos->root, 0);

     // Initialiser l'arbre à partir de la position (1, 1) avec 5 niveaux
     buildTree(map, 1, 1, 2);
     return 0;
 }
