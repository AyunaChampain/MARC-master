//
// Created by ayuna on 16/11/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "bot.h"
#include "nbinarytree.h"
#include "map.h"
#include "node.h"
#include "loc.h"
#include "moves.h"
#include "stack.h"
#include "queue.h"

int isValidPosition(int x, int y, t_map map) {
    return x >= 0 && x < map.x_max && y >= 0 && y < map.y_max;
}


void addNeighborsAsChildrenRecursive(p_nnode node, t_localisation loc, t_map map, int depth) {
    if (depth <= 0) {
        return;  // Stop recursion at depth 0
    }

    t_move moves[] = {F_10, F_20, B_10, T_LEFT, T_RIGHT, U_TURN};

    // Try each move
    for (int i = 0; i < 6; i++) {  // Updated to loop through all 6 possible moves
        t_move mov = moves[i];
        t_localisation next_loc = move(loc, mov);

        // Check if the position is valid
        if (isValidPosition(next_loc.pos.x, next_loc.pos.y, map)) {  // Corrected validation
            int cost = map.costs[next_loc.pos.y][next_loc.pos.x];

            // Create the child node and assign the move leading to it
            p_nnode child = createNode(cost, next_loc.pos.x, next_loc.pos.y, mov);

            // Add child to the parent node
            add_child(node, child);

            // Recursive call for this child
            addNeighborsAsChildrenRecursive(child, next_loc, map, depth - 1);
        }
    }
}


p_nnode buildTree(t_map map, int posx, int posy, int depth)
{
    t_localisation start_loc = loc_init(posx, posy, NORTH); // Starting orientation
    int root_cost = map.costs[posy][posx];

    // Root node with no movement leading to it (initial state)
    p_nnode root = createNode(root_cost, posx, posy, F_10);

    // Add neighbors recursively
    addNeighborsAsChildrenRecursive(root, start_loc, map, depth); // Increase depth here

    return root;
}


void move_robot_and_print(t_localisation *loc, t_move movement, t_map map) {
    // Perform the movement but check if it stays within bounds first
    t_localisation new_loc = move(*loc, movement);

    // Check if the new position is within bounds
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
        // Print a warning if the move goes out of bounds
        printf("Invalid move: The robot cannot move out of bounds to (%d, %d).\n", new_loc.pos.x, new_loc.pos.y);
    }
}




void bot_function(struct s_map map, int arx, int ary) {
    int cpt = 1;

    t_localisation loc = loc_init(4, 6, NORTH);  // Starting position and orientation
    p_nnode chemin_complet[1000];  // Full path
    int chemin_complet_index = 0;

    while (loc.pos.x != arx || loc.pos.y != ary) {
        printf("%dth phase\n", cpt);

        // Build the tree
        p_nnode root = buildTree(map, loc.pos.x, loc.pos.y, 5);
        p_nnode min = searchleaf(root, root);  // Find the minimum-cost leaf
        printf("Minimum value in tree: %d\n", min->value);

        p_nnode chemin[100];
        int index = 0;

        // Find the path to the minimum-cost node
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

        // Add the found path to the full path
        for (int i = 0; i < index; i++) {
            chemin_complet[chemin_complet_index++] = chemin[i];
        }

        // Execute the moves and check if we're at the base
        for (int i = 0; i < chemin_complet_index; i++) {
            t_move move = chemin_complet[i]->movement;
            move_robot_and_print(&loc, move, map);  // Pass map for validation

            // After each move, check if the robot has reached the target position
            if (loc.pos.x == arx && loc.pos.y == ary) {
                printf("Target reached: (%d, %d)\n", loc.pos.x, loc.pos.y);
                return;  // Exit the function as the robot has reached the base
            }
        }

        cpt++;
    }

    // If the loop exits, the target was reached
    printf("Final position: (%d, %d), orientation: %d\n", loc.pos.x, loc.pos.y, loc.ori);
}
