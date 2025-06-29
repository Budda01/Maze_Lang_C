#include "base_algorithm.h"

// Рекурсивный перебор направлений
int dfs_search(Maze* maze, int x, int y, int end_x, int end_y, int* path_len) {
  int found = 0;

  for (int dir = 0; dir < DIRECTIONS && !found; dir++) {
    int can_move = 0;
    int nx = x;
    int ny = y;

    switch (dir) {
      case 0:  // вправо
        if (maze->maze[x][y].right == 0) {
          can_move = 1;
          ny = y + 1;
        }
        break;
      case 1:  // вниз
        if (maze->maze[x][y].bottom == 0) {
          can_move = 1;
          nx = x + 1;
        }
        break;
      case 2:  // влево
        if (y > 0 && maze->maze[x][y - 1].right == 0) {
          can_move = 1;
          ny = y - 1;
        }
        break;
      case 3:  // вверх
        if (x > 0 && maze->maze[x - 1][y].bottom == 0) {
          can_move = 1;
          nx = x - 1;
        }
        break;
      default:
        can_move = 0;
    }

    if (can_move) {
      found = dfs(maze, nx, ny, end_x, end_y, path_len);
    }
  }

  return found;
}

// Основной DFS
int dfs(Maze* maze, int x, int y, int end_x, int end_y, int* path_len) {
  int found = 0;

  if (x < 0 || y < 0 || x >= maze->height || y >= maze->width) {
    found = 0;
  } else if (maze->visited[x][y]) {
    found = 0;
  } else {
    maze->visited[x][y] = 1;
    maze->path[*path_len].x = x;
    maze->path[*path_len].y = y;
    (*path_len)++;

    if (x == end_x && y == end_y) {
      found = 1;
    } else {
      found = dfs_search(maze, x, y, end_x, end_y, path_len);
    }

    if (!found) {
      (*path_len)--;  // backtrack
    }
  }

  return found;
}

int solve_maze(Maze* maze, Coord start, Coord end) {
  for (int i = 0; i < maze->height; i++)
    for (int j = 0; j < maze->width; j++) maze->visited[i][j] = 0;

  maze->path_length = 0;

  int result = dfs(maze, start.x, start.y, end.x, end.y, &maze->path_length);
  return result;
}