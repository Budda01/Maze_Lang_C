#include "maze.h"

#include <time.h>

#include "base_algorithm.h"

int read_maze(Maze* maze, const char* filename) {
  int check = 0;
  FILE* file = fopen(filename, "r");
  if (!file) check = 1;
  if (!check) {
    check = file_reader(maze, file);
    fclose(file);
  }
  return check;
}

int file_reader(Maze* maze, FILE* file) {
  int check = 0;
  if (fscanf(file, "%d %d", &maze->height, &maze->width) != 2) check = 1;
  if (maze->height > MAX_SIZE || maze->width > MAX_SIZE) check = 1;

  if (!check) {
    for (int i = 0; i < maze->height; i++) {
      for (int j = 0; j < maze->width; j++) {
        if (fscanf(file, "%d", &maze->maze[i][j].right) != 1) check++;
      }
    }

    for (int i = 0; i < maze->height; i++) {
      for (int j = 0; j < maze->width; j++) {
        if (fscanf(file, "%d", &maze->maze[i][j].bottom) != 1) check++;
      }
    }
  }
  return check;
}

int save_maze(const Maze* maze, const char* filename) {
  FILE* file = fopen(filename, "w");
  if (!file) {
    return 1;
  }
  fprintf(file, "%d %d\n", maze->height, maze->width);
  for (int i = 0; i < maze->height; i++) {
    for (int j = 0; j < maze->width; j++) {
      fprintf(file, "%d", maze->maze[i][j].right);
      if (j < maze->width - 1) fprintf(file, " ");
    }
    fprintf(file, "\n");
  }
  fprintf(file, "\n");
  for (int i = 0; i < maze->height; i++) {
    for (int j = 0; j < maze->width; j++) {
      fprintf(file, "%d", maze->maze[i][j].bottom);
      if (j < maze->width - 1) fprintf(file, " ");
    }
    fprintf(file, "\n");
  }

  fclose(file);
  return 0;
}

void comp_maze_decode(Maze* maze) {
  for (int i = 0; i < maze->height; i++) {
    for (int j = 0; j < maze->width; j++) {
      int code = maze->maze_code[i][j];
      maze->maze[i][j].right = 0;
      maze->maze[i][j].bottom = 0;

      if (code & 2) maze->maze[i][j].bottom = 1;
      if (code & 4) maze->maze[i][j].right = 1;
    }
  }
}

void comp_maze_code(Maze* maze) {
  for (int i = 0; i < maze->height; i++) {
    for (int j = 0; j < maze->width; j++) {
      int code = 0;
      if (maze->maze[i][j].right == 1) code |= 4;
      if (maze->maze[i][j].bottom == 1) code |= 2;
      if ((j > 0 && maze->maze[i][j - 1].right == 1) || j == 0) code |= 1;
      if ((i > 0 && maze->maze[i - 1][j].bottom == 1) || i == 0) code |= 8;
      maze->maze_code[i][j] = code;
    }
  }
}

// void print_maze_proc(const Maze* maze) {
//   printf("Матрица кодов стен (0–15):\n");
//   for (int i = 0; i < maze->height; i++) {
//     for (int j = 0; j < maze->width; j++) {
//       printf("%2d ", maze->maze_code[i][j]);
//     }
//     printf("\n");
//   }
// }

// void print_maze_values(const Maze* maze) {
//   printf("Матрица ячеек (формат: (right,bottom)):\n");

//   for (int i = 0; i < maze->height; i++) {
//     for (int j = 0; j < maze->width; j++) {
//       printf("(%d,%d) ", maze->maze[i][j].right, maze->maze[i][j].bottom);
//     }
//     printf("\n");
//   }
// }

void shuffle(int* arr, int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}

void dfs_maze_gen(Maze* maze, int x, int y, int visited[MAX_SIZE][MAX_SIZE]) {
  visited[x][y] = 1;

  int dirs[4] = {0, 1, 2, 3};  // 0: up, 1: right, 2: down, 3: left
  shuffle(dirs, 4);

  for (int i = 0; i < 4; i++) {
    int nx = x, ny = y;

    if (dirs[i] == 0) nx--;
    if (dirs[i] == 1) ny++;
    if (dirs[i] == 2) nx++;
    if (dirs[i] == 3) ny--;

    if (nx < 0 || ny < 0 || nx >= maze->height || ny >= maze->width) continue;

    if (!visited[nx][ny]) {
      // Удаление стены между (x,y) и (nx,ny)
      if (dirs[i] == 0) maze->maze[nx][ny].bottom = 0;   // вверх
      if (dirs[i] == 1) maze->maze[x][y].right = 0;      // вправо
      if (dirs[i] == 2) maze->maze[x][y].bottom = 0;     // вниз
      if (dirs[i] == 3) maze->maze[x][y - 1].right = 0;  // влево

      dfs_maze_gen(maze, nx, ny, visited);
    }
  }
}

void generate_perfect_maze(Maze* maze, int height, int width) {
  maze->height = height;
  maze->width = width;

  // Изначально все стены закрыты
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      maze->maze[i][j].right = 1;
      maze->maze[i][j].bottom = 1;
    }
  }

  int visited[MAX_SIZE][MAX_SIZE] = {0};
  srand(time(NULL));

  int start_x = rand() % height;
  int start_y = rand() % width;
  dfs_maze_gen(maze, start_x, start_y, visited);
}
