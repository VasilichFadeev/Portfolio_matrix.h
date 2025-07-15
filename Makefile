CC = gcc
CFLAGS = -Wall -Wextra -Werror
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS_MACOS = -lcheck -lm -lpthread
LDFLAGS_LINUX = -lcheck -lm -lpthread -lsubunit
TEST_SOURCES = s21_test.c $(wildcard functions/*.c) $(wildcard functions/helpers/*.c)
LIB_SOURCES = $(wildcard functions/*.c)	$(wildcard functions/helpers/*.c)
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)
TEST_EXEC = s21_test
GCOV_EXEC = s21_test_gcov
REPORT_DIR = report
OBJ_DIR = obj
LIB_NAME = s21_matrix.a

UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
    LDFLAGS = $(LDFLAGS_MACOS)
else
    LDFLAGS = $(LDFLAGS_LINUX)
    CFLAGS += -std=c11
endif

all: $(LIB_SOURCES)
	$(CC) $(CFLAGS) -c $(LIB_SOURCES)
	ar rcs $(LIB_NAME) *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_SOURCES)
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_EXEC) $(LDFLAGS)
	./$(TEST_EXEC)

s21_matrix.a: $(LIB_SOURCES)
	$(CC) $(CFLAGS) -c $(LIB_SOURCES)
	ar rcs $(LIB_NAME) *.o
	rm -f *.o

$(GCOV_EXEC): $(TEST_SOURCES)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SOURCES) -o $(GCOV_EXEC) $(LDFLAGS)
	mv *.gcno $(OBJ_DIR)

gcov_report: $(GCOV_EXEC)
	mkdir -p $(REPORT_DIR)
	./$(GCOV_EXEC)
	mv *.gcda $(OBJ_DIR)
	lcov -t "$(GCOV_EXEC)" -o $(REPORT_DIR)/coverage.info -c -d $(OBJ_DIR)
	genhtml -o $(REPORT_DIR) $(REPORT_DIR)/coverage.info
	open report/index.html

clean:
	rm -rf $(TEST_EXEC) $(GCOV_EXEC) $(REPORT_DIR) $(OBJ_DIR) $(LIB_NAME) *.gcda *.gcno *.info
	find . -name '*.o' -delete

check_style:
	cd ../materials/linters && clang-format -n ../../src/*.c ../../src/*.h ../../src/functions/*.c ../../src/functions/helpers/*.c

clang-format:
	cd ../materials/linters && clang-format -i ../../src/*.c ../../src/*.h ../../src/functions/*.c ../../src/functions/helpers/*.c

valgrind:
	make test
	valgrind --tool=memcheck --leak-check=yes ./s21_test
	rm -rf ./s21_test

leaks:
	make test
	leaks -atExit -- ./s21_test
	rm -rf ./s21_test

mini_verter:
	cd ../materials/build && bash run.sh

.PHONY: all test gcov_report s21_matrix.a clean
