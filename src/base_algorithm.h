#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "maze.h"
#define DIRECTIONS 4

int dfs_search(Maze* maze, int x, int y, int end_x, int end_y, int* path_len);
int solve_maze(Maze* maze, Coord start, Coord end);
int dfs(Maze* maze, int x, int y, int end_x, int end_y, int* path_len);

#endif
