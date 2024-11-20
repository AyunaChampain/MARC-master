#ifndef BOT_H
#define BOT_H

#include "map.h"
#include "node.h"
#include "loc.h"
#include "moves.h"
#include "nbinarytree.h"

// Move selection structure with weighted probabilities
typedef struct {
    t_move move;
    double probability;
} t_weighted_move;

// Function declarations

// Helper functions
int isValidPosition(int x, int y, t_map map);

// Random move selection functions
t_move choose_random_move(t_weighted_move moves[], int size);
void generate_random_moves_pool(t_move pool[], int pool_size, t_weighted_move moves[], int num_moves);
void print_moves_pool(t_move pool[], int pool_size);

// Tree-building functions
void addNeighborsAsChildrenRecursive(p_nnode node, t_localisation loc, t_map map, int depth, int max_moves, t_move pool[], int pool_size, int reg) ;
p_nnode buildTree(t_map map, int posx, int posy, int depth, int max_moves, t_move pool[], int pool_size, int reg) ;

// Movement functions
void move_robot_and_print(t_localisation *loc, t_move movement, t_map map, int* reg);
void remove_move_from_pool(t_move pool[], int *pool_size, t_move move);
// Main bot function
void bot_function(struct s_map map, int arx, int ary);

#endif // BOT_H
