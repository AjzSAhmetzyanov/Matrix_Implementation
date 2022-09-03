.PHONY: all  clean test  s21_matrix_oop.a objects build_lib rebuild clean_obj
CC=gcc
CFLAGS=-Wall -Werror -Wextra -lstdc++

all: test

s21_matrix_oop.a: build_lib clean_obj

build_lib: objects
	@ar rc s21_matrix_oop.a s21_matrix_oop.o
	@ranlib s21_matrix_oop.a

objects:
	@$(CC) $(CFLAGS) -c s21_matrix_oop.cc

test: s21_matrix_oop.a s21_matrix_test.cc
	@$(CC) $(CFLAGS) -lgtest s21_matrix_test.cc s21_matrix_oop.a -o test
	@./test

check: test
	clang-format -n *.cc *.h
	leaks -atExit -- test

clean_obj:
	@rm -rf *.o

clean:
	@rm -rf *.a ./test
	# @rm -rf ./test

rebuild: clean all