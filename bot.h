//
// Created by ayuna on 16/11/2024.
//
#include "nbinarytree.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#ifndef UNTITLED1_BOT_H
#define UNTITLED1_BOT_H


void addNeighborsAsChildren(p_nnode, t_position, t_map);
p_nnode buildTree(t_map, int, int, int);
void addNeighborsAsChildrenRecursive(p_nnode, t_position, t_map, int) ;

void bot_function(struct s_map, int, int) ;
t_move adjustMoveForTerrain(t_localisation loc, t_move move, t_soil map[6][7]);


#endif //UNTITLED1_BOT_H
