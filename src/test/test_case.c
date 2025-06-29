#include <stdio.h>

#include "tests.h"

START_TEST(test_file_input_valid_file) {
  Maze maze = {0};
  FILE* input_file = fopen("test_input.txt", "w");
  fprintf(input_file, "test/sample1.txt\n");
  fclose(input_file);

  freopen("test_input.txt", "r", stdin);

  file_input(&maze);

  ck_assert_int_eq(maze.height, 4);
  ck_assert_int_eq(maze.width, 4);

  fclose(stdin);
}
END_TEST

START_TEST(test_read_maze_invalid_file) {
  Maze maze = {0};
  int result = read_maze(&maze, "non_existing_file.txt");
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_read_maze_valid_file) {
  Maze maze = {0};
  int result = read_maze(&maze, "sample3.txt");
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_maze_path) {
  Maze maze = {0};
  FILE* input_file_load = fopen("test_input.txt", "w");
  fprintf(input_file_load, "test/sample4.txt\n");
  fclose(input_file_load);

  freopen("test_input.txt", "r", stdin);
  file_input(&maze);
  ck_assert_int_eq(maze.height, 4);
  ck_assert_int_eq(maze.width, 4);
  fclose(stdin);
  FILE* input_file_solve = fopen("test_solve_input.txt", "w");
  fprintf(input_file_solve,
          "3 3\n0 0\n");  // например, старт (0,0), финиш (3,3)
  fclose(input_file_solve);
  freopen("test_solve_input.txt", "r", stdin);
  solve_input(&maze);

  ck_assert_int_eq(maze.height, 4);
  ck_assert_int_eq(maze.width, 4);

  fclose(stdin);
}
END_TEST

START_TEST(test_maze_path2) {
  Maze maze = {0};
  FILE* input_file_load = fopen("test_input.txt", "w");
  fprintf(input_file_load, "test/sample4.txt\n");
  fclose(input_file_load);

  freopen("test_input.txt", "r", stdin);
  file_input(&maze);
  ck_assert_int_eq(maze.height, 4);
  ck_assert_int_eq(maze.width, 4);
  fclose(stdin);
  FILE* input_file_solve = fopen("test_solve_input.txt", "w");
  fprintf(input_file_solve,
          "1 0\n1 3\n");  // например, старт (0,0), финиш (3,3)
  fclose(input_file_solve);
  freopen("test_solve_input.txt", "r", stdin);
  solve_input(&maze);

  ck_assert_int_eq(maze.height, 4);
  ck_assert_int_eq(maze.width, 4);

  fclose(stdin);
}
END_TEST

START_TEST(test_gen_input_valid) {
  Maze maze = {0};

  FILE* input_file = fopen("test_gen_input_valid.txt", "w");
  fprintf(input_file, "10 15\n");
  fclose(input_file);

  freopen("test_gen_input_valid.txt", "r", stdin);

  gen_input(&maze);

  ck_assert_int_eq(maze.height, 10);
  ck_assert_int_eq(maze.width, 15);

  fclose(stdin);
}
END_TEST

Suite* s21_maze_test(void) {
  Suite* s = suite_create("Maze Tests");

  // Первый TCase: File Input
  TCase* tc_file = tcase_create("File Input");
  tcase_add_test(tc_file, test_file_input_valid_file);
  suite_add_tcase(s, tc_file);

  // Второй TCase: Read Maze Errors
  TCase* tc_read = tcase_create("Read Maze");
  tcase_add_test(tc_read, test_read_maze_invalid_file);
  tcase_add_test(tc_read, test_read_maze_valid_file);
  tcase_add_test(tc_read, test_maze_path);
  tcase_add_test(tc_read, test_maze_path2);
  tcase_add_test(tc_read, test_gen_input_valid);

  suite_add_tcase(s, tc_read);

  return s;
}
