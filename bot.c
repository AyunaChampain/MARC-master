#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bot.h"
#include "nbinarytree.h"
#include "map.h"
#include "node.h"
#include "loc.h"
#include "moves.h"
#include "stack.h"
#include "queue.h"

// Define constants
#define NUM_MOVES 7
#define RANDOM_POOL_SIZE 9



// Weighted moves
t_weighted_move weighted_moves[NUM_MOVES] = {
        {F_10, 22.0}, {F_20, 15.0}, {F_30, 7.0},
        {B_10, 7.0}, {T_LEFT, 21.0}, {T_RIGHT, 21.0}, {U_TURN, 7.0}
};

// Function to choose a random move based on current probabilities
t_move choose_random_move(t_weighted_move moves[], int size) {
    double total_weight = 0.0;

    for (int i = 0; i < size; i++) {
        total_weight += moves[i].probability;
    }

    double random_value = ((double)rand() / RAND_MAX) * total_weight;

    for (int i = 0; i < size; i++) {
        if (random_value < moves[i].probability) {
            return moves[i].move;
        }
        random_value -= moves[i].probability;
    }

    return moves[0].move; // Default fallback
}

// Function to generate a pool of 9 random moves
void generate_random_moves_pool(t_move pool[], int pool_size, t_weighted_move moves[], int num_moves) {
    for (int i = 0; i < pool_size; i++) {
        pool[i] = choose_random_move(moves, num_moves);
    }
}

// Function to print the generated moves
void print_moves_pool(t_move pool[], int pool_size) {
    printf("Generated Moves Pool: ");
    for (int i = 0; i < pool_size; i++) {
        printf("%s ", getMoveAsString(pool[i])); // Assuming getMoveAsString converts move to a string
    }
    printf("\n");
}

// Helper function to check if position is valid
int isValidPosition(int x, int y, t_map map) {
    return x >= 0 && x < map.x_max && y >= 0 && y < map.y_max;
}

// Recursive function to add neighbors as children to the tree
void addNeighborsAsChildrenRecursive(p_nnode node, t_localisation loc, t_map map, int depth, int max_moves, t_move pool[], int pool_size) {
    if (depth <= 0 || max_moves <= 0) {
        return;
    }

    for (int i = 0; i < pool_size; i++) {
        t_move mov = pool[i];
        t_localisation next_loc = move(loc, mov);

        if (isValidPosition(next_loc.pos.x, next_loc.pos.y, map)) {
            int cost = map.costs[next_loc.pos.y][next_loc.pos.x];
            p_nnode child = createNode(cost, next_loc.pos.x, next_loc.pos.y, mov);
            add_child(node, child);
            addNeighborsAsChildrenRecursive(child, next_loc, map, depth - 1, max_moves - 1, pool, pool_size);
        }
    }
}

// Build the tree based on the current position and moves pool
p_nnode buildTree(t_map map, int posx, int posy, int depth, int max_moves, t_move pool[], int pool_size) {
    t_localisation start_loc = loc_init(posx, posy, NORTH); // Starting orientation
    int root_cost = map.costs[posy][posx];

    // Root node with no movement leading to it (initial state)
    p_nnode root = createNode(root_cost, posx, posy, F_10);

    // Add neighbors recursively
    addNeighborsAsChildrenRecursive(root, start_loc, map, depth, max_moves, pool, pool_size);

    return root;
}

// Function to perform the robot movement and print the result
void move_robot_and_print(t_localisation *loc, t_move movement, t_map map, int* reg) {
    t_soil terrain_type = map.soils[loc->pos.y][loc->pos.x];  // Assuming soils is a 2D array

    if (terrain_type == ERG) {
        if (movement == F_10) {
            movement = 0;  // No movement
        } else if (movement == F_20) {
            movement = F_10;  // Only move 10m
        } else if (movement == F_30) {
            movement = F_20;  // Only move 20m
        }

        if (movement == U_TURN) {
            movement = (rand() % 2) ? T_LEFT : T_RIGHT;
        }
    }

    t_localisation new_loc = move(*loc, movement);

    if (isValidPosition(new_loc.pos.x, new_loc.pos.y, map)) {
        if (movement == T_LEFT || movement == T_RIGHT || movement == U_TURN) {
            printf("Turn: %s\n", getMoveAsString(movement));
            *loc = new_loc;  // Only update orientation
        } else {
            printf("Move: %s\n", getMoveAsString(movement));
            *loc = new_loc;  // Update both position and orientation
        }
        printf("Updated position: (%d, %d), orientation: %d\n", loc->pos.x, loc->pos.y, loc->ori);
    } else {
        printf("Invalid move: The robot cannot move out of bounds to (%d, %d).\n", new_loc.pos.x, new_loc.pos.y);
    }

    if (terrain_type == REG) {
        printf("Robot has been shaken on Reg terrain. Limiting next phase to 4 moves.\n");
        *reg = 1;
    }
}

// Main bot function
void bot_function(struct s_map map, int arx, int ary) {
    int cpt = 1;  // Phase counter
    int reg = 0 ;

    t_localisation loc = loc_init(5, 6, NORTH);  // Starting position and orientation
    p_nnode chemin_complet[1000];  // Full path
    int chemin_complet_index = 0;

    // Generate a random pool of moves
    t_move random_moves_pool[RANDOM_POOL_SIZE];
    generate_random_moves_pool(random_moves_pool, RANDOM_POOL_SIZE, weighted_moves, NUM_MOVES);
    print_moves_pool(random_moves_pool, RANDOM_POOL_SIZE);

    while (loc.pos.x != arx || loc.pos.y != ary) {
        printf("\n=========================\n");
        printf("Phase #%d\n", cpt);
        printf("=========================\n");

        p_nnode root = buildTree(map, loc.pos.x, loc.pos.y, 5, 9, random_moves_pool, RANDOM_POOL_SIZE);
        p_nnode min = searchmin(root, root);  // Find the minimum-cost leaf
        printf("Minimum value in tree: %d\n", min->value);

        p_nnode chemin[100];
        int index = 0;

        if (findpath(root, min, chemin, &index)) {
            printf("Path from root to min: ");
            for (int i = 0; i < index; i++) {
                printf("[%d] ", chemin[i]->value);
            }
            printf("\n");
        } else {
            printf("No path found to min.\n");
            break;
        }

        for (int i = 0; i < index; i++) {
            chemin_complet[chemin_complet_index++] = chemin[i];
        }

        for (int i = 1; i < index; i++) {
            t_move move = chemin[i]->movement;
            move_robot_and_print(&loc, move, map, &reg);

            if ((loc.pos.x == arx && loc.pos.y == ary) || map.costs[loc.pos.y][loc.pos.x] == 0) {
                printf("Target or base reached in phase #%d: (%d, %d)\n", cpt, loc.pos.x, loc.pos.y);
                return;
            }
        }

        if (cpt == 4 && reg == 1) {
            printf("Only 4 moves allowed in the next phase due to Reg terrain.\n");
            break;
        }

        cpt++;
        if (cpt == 5) {
            break;
        }
    }

    printf("Final position: (%d, %d), orientation: %d\n", loc.pos.x, loc.pos.y, loc.ori);
}
