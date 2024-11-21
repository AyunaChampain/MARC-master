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

     int choice = 0 ;

     printf("Quel scénario voulez-vous tester ? (Entre 0 et 3) ") ;
     scanf("%d", &choice) ;

     //Génère la map du scénario choisi
     if (choice == 0)
     {
        #if defined(_WIN32) || defined(_WIN64)
                 map = createMapFromFile("..\\maps\\example1.map");
        #else
                 map = createMapFromFile("../maps/example1.map");
        #endif
     }
     if (choice == 1)
     {
        #if defined(_WIN32) || defined(_WIN64)
                 map = createMapFromFile("..\\maps\\map1.map");
        #else
                 map = createMapFromFile("../maps/example1.map");
        #endif
     }
     if (choice == 2)
     {
        #if defined(_WIN32) || defined(_WIN64)
                 map = createMapFromFile("..\\maps\\map2.map");
        #else
                 map = createMapFromFile("../maps/example1.map");
        #endif
     }
     if (choice == 3)
     {
        #if defined(_WIN32) || defined(_WIN64)
                 map = createMapFromFile("..\\maps\\map4.map");
        #else
                 map = createMapFromFile("../maps/example1.map");
        #endif
     }


     //Code de base pour créer et afficher la map -----------------------------------------------------------------------------------------------

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

    int x = 0 ;
    int y = 0 ;

    //Initialise les positions du bot selon le scénario choisi
    if (choice == 0)
    {
        x = 4 ;
        y = 5 ;
    }
     if (choice == 1)
     {
         x = 0 ;
         y = 5 ;
     }
     if (choice == 2)
     {
         x = 1 ;
         y = 1 ;
     }
     if (choice == 3)
     {
         x = 2 ;
         y = 1 ;
     }


     srand((unsigned int)time(NULL)); //Permet de gérer une génération aléatoire
     bot_function(map, x, y); //Appelle la fonction utilisée pour faire fonctionner le robot

     return 0;
 }
