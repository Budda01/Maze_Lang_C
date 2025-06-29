#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef struct {
  int right;
  int bottom;
} Cell;

typedef struct {
  int x;
  int y;
} Coord;

typedef struct Maze {
  int height;
  int width;
  Cell maze[MAX_SIZE][MAX_SIZE];
  int maze_code[MAX_SIZE][MAX_SIZE];
  Coord path[MAX_SIZE * MAX_SIZE];
  int path_length;
  int visited[MAX_SIZE][MAX_SIZE];
} Maze;

void menu_and_actions(Maze* maze);
void file_input(Maze* maze);
void gen_input(Maze* maze);
void draw_menu();
void menu_and_actions(Maze* maze);
void save_input(Maze* maze);
void solve_input(Maze* maze);

int read_maze(Maze* maze, const char* filename);
int save_maze(const Maze* maze, const char* filename);
int file_reader(Maze* maze, FILE* file);
void comp_maze_code(Maze* maze);
void comp_maze_decode(Maze* maze);
void shuffle(int* arr, int n);
void draw_maze(const Maze* m);
void dfs_maze_gen(Maze* maze, int x, int y, int visited[MAX_SIZE][MAX_SIZE]);
void generate_perfect_maze(Maze* maze, int height, int width);

void print_maze_proc(const Maze* maze);
void print_maze_values(const Maze* maze);

#endif