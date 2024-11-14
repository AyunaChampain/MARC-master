 #include <stdio.h>
#include "map.h"
#include "nbinarytree.h"
#include "node.h"

//Github test !

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
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

    t_nnode node ;
    p_tree Tree ;
    Tree = create_empty_tree();
    add_node(Tree, 2);
    display_tree(Tree);


    return 0;
}
