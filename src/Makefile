.PHONY: all clean tests gcov_report style

GCC = gcc -Wall -Werror -Wextra -std=c11

OS := $(shell uname -s)
TARGET= adelinan_s21_SmartCalc

ifeq ($(OS), Linux)
	LIB = -lcheck -lrt -lpthread -lsubunit -lm
	LEAK = valgrind --tool=memcheck --leak-check=yes
	OPEN = xdg-open
endif

ifeq ($(OS), Darwin)
	LIB = -lcheck
	OPEN = open
endif

all: install


install:
	$(GCC) -c maze.c
	$(GCC) -c base_algorithm.c
	$(GCC) -c view.c
	$(GCC) -c main.c
	$(GCC) maze.o main.o base_algorithm.o view.o -o maze
	

uninstall: clean
	@rm -rf maze
	
tests: 
	$(GCC) test/*.c maze.c base_algorithm.c view.c -o s21_tests $(LIB)
	@./s21_tests


gcov_report :
	@$(GCC) test/*.c maze.c base_algorithm.c view.c --coverage $(LIB) -o s21_tests
	@./s21_tests
	@mkdir ./report 
	@mv *.g* ./report
	@lcov -c -q -d ./report -o ./report/coverage.info
	@genhtml -q ./report/coverage.info -o ./report
	@$(OPEN) report/index.html


style:
	@clang-format -style=Google -n *.c
	@clang-format -style=Google -n *.h
	@clang-format -style=Google -n test/*.c
	@clang-format -style=Google -n test/*.h

clean :
	@rm -rf *.o *.a s21_tests *.gcda *.txt *.gcno coverage.info ./report tmp


