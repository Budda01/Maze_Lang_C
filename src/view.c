#include "base_algorithm.h"
#include "maze.h"

void draw_maze(const Maze* m) {
  int h = m->height;
  int w = m->width;
  int is_in_path[MAX_SIZE][MAX_SIZE] = {0};
  if (m->path_length != 0) {
    for (int i = 0; i < m->path_length; i++) {
      if (m->path[i].x >= 0 && m->path[i].x < h && m->path[i].y >= 0 &&
          m->path[i].y < w) {
        is_in_path[m->path[i].x][m->path[i].y] = 1;
      }
    }
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("\033[32m+");  // угол
      if (m->maze_code[i][j] & 8)
        printf("────");  // верхняя стена
      else
        printf("    ");
    }
    printf("+\033[0m\n");  // правый край строки
    for (int j = 0; j < w; j++) {
      if (m->maze_code[i][j] & 1)
        printf("\033[32m│");
      else
        printf(" ");
      if (is_in_path[i][j])
        printf("\033[94m ▒▒ \033[0m");  // путь
      else
        printf("    ");
    }
    if (m->maze_code[i][w - 1] & 4)
      printf("\033[32m│\n");
    else
      printf(" \n");
    printf("\033[0m");  // сброс цвета
  }
  for (int j = 0; j < w; j++) {
    printf("\033[32m+");
    if (m->maze_code[h - 1][j] & 2)
      printf("────");
    else
      printf("    ");
  }
  printf("+\033[0m\n");
}

void file_input(Maze* maze) {
  char filename[256];
  printf("Введите имя файла для загрузки лабиринта: ");
  scanf("%255s", filename);
  if (read_maze(maze, filename) != 0)
    printf("Не удалось загрузить файл '%s'. Проверьте имя и содержимое.\n",
           filename);
  else {
    printf("Лабиринт успешно загружен из '%s'.\n", filename);
    comp_maze_code(maze);
    draw_maze(maze);
  }
}

void gen_input(Maze* maze) {
  int height, width;
  int check = 0;
  printf("Введите размеры генерируемого лабиринта.\n");
  if (scanf("%d %d", &height, &width) != 2) {
    printf("Неверный ввод. Введите два целых числа.\n");
    while (getchar() != '\n')
      ;
    check = 1;
  }
  if (!check &&
      (height <= 0 || height > MAX_SIZE || width <= 0 || width > MAX_SIZE)) {
    printf("Размеры лабиринта должны быть от 1 до 50.\n");
    check = 1;
  }
  if (!check) {
    generate_perfect_maze(maze, height, width);
    comp_maze_code(maze);
    printf("Лабиринт %dx%d успешно сгенерирован.\n", height, width);
    draw_maze(maze);
  }
}

void save_input(Maze* maze) {
  char filename[256];
  int check = 0;
  printf("Введите имя файла сохранения лабиринта: ");
  scanf("%255s", filename);
  if (maze->height != 0)
    check = save_maze(maze, filename);
  else
    check = 1;
  if (!check)
    printf("Файл успешно сохранен");
  else
    printf("Произошла ошибка при сохранении");
}

void solve_input(Maze* maze) {
  if (maze->height == 0 || maze->width == 0) {
    printf("Лабиринт отсутствует. Сначала загрузите или сгенерируйте его.\n");
    return;
  }
  Coord start, end;
  printf("Введите координаты старта (x y): ");
  if (scanf("%d %d", &start.x, &start.y) != 2) {
    printf("Неверный ввод координат старта.\n");
    while (getchar() != '\n')
      ;
    return;
  }
  printf("Введите координаты финиша (x y): ");
  if (scanf("%d %d", &end.x, &end.y) != 2) {
    printf("Неверный ввод координат финиша.\n");
    while (getchar() != '\n')
      ;
    return;
  }
  if (solve_maze(maze, start, end)) {
    printf("Путь найден:\n");
    draw_maze(maze);
  } else {
    printf("Путь не найден.\n");
  }
}

void draw_menu() {
  system("clear");
  printf("╔══════════════════════════════════════╗\n");
  printf("║           Выберите действие          ║\n");
  printf("╠══════════════════════════════════════╣\n");
  printf("║ 1.   Загрузить лабиринт из файла     ║\n");
  printf("║ 2.   Сгенерировать новый лабиринт    ║\n");
  printf("║ 3.   Сохранить лабиринт в файл       ║\n");
  printf("║ 4.     Найти путь в лабиринте        ║\n");
  printf("║ 5.       Выход из программы          ║\n");
  printf("╚══════════════════════════════════════╝\n");
}

void menu_and_actions(Maze* maze) {
  int choice = -1;
  int exit = 0;
  Maze empty = {0};
  while (!exit) {
    draw_menu();
    printf("Введите номер варианта: ");
    if (scanf("%d", &choice) != 1) {
      while (getchar() != '\n')
        ;
    }
    system("clear");
    switch (choice) {
      case 1:
        *maze = empty;
        file_input(maze);
        break;
      case 2:
        *maze = empty;
        gen_input(maze);
        break;
      case 3:
        save_input(maze);
        break;
      case 4:
        solve_input(maze);
        break;
      case 5:
        exit = 1;
        break;
      default:
        printf("Неверный выбор. Попробуйте снова.\n");
        continue;
    }
    if (!exit) {
      printf("\nНажмите Enter, чтобы вернуться в меню...");
      while (getchar() != '\n')
        ;
      getchar();
    }
  }
}