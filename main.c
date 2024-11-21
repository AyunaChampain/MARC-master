 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
     //Code de base pour créer et afficher la map -----------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
    int x = 5; //position x du robot
    int y = 6; //position y du robot

     srand((unsigned int)time(NULL)); //Permet de gérer une génération aléatoire
     bot_function(map, x, y); //Appelle la fonction utilisée pour faire fonctionner le robot

     return 0;
 }
