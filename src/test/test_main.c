#include <stdio.h>

#include "tests.h"

int main() {
  int failed = 0;

  Suite* suites[] = {s21_maze_test(), NULL};

  for (int i = 0; suites[i] != NULL; i++) {
    printf("-----------------------------------------------\n");

    SRunner* sr = srunner_create(suites[i]);
    srunner_set_fork_status(sr,
                            CK_NOFORK);  // для отображения printf внутри тестов
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  if (failed == 0) {
    printf(
        "\033[32m------------------- SUCCESS -------------------\033[0m\n\n");
  } else {
    printf("\033[31m------------------ FAILED: %d -----------------\033[0m\n\n",
           failed);
  }

  return (failed == 0) ? 0 : 1;
}
