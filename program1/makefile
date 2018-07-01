# File: makefile
# Description: Basic makefile for automated buidls
CC := g++
CFLAGS := -std=c++98 -Wall -I ../third_party/ -I include -I src
TESTS_SRC := ../third_party/tests_main.cpp
TESTS_MAIN := ../third_party/tests_main.o

obj/debug/runTests: obj/linked_list.o obj/list_test.o obj/sstring_test.o obj/project_test.o obj/project.o obj/category.o obj/sstring.o $(TESTS_MAIN)
	$(CC) $(CFLAGS) obj/linked_list.o obj/list_test.o obj/sstring_test.o obj/project_test.o obj/project.o obj/category.o obj/sstring.o $(TESTS_MAIN) -o obj/debug/runTests

obj/project_test.o: tests/project_test.cpp
	$(CC) $(CFLAGS) -c tests/project_test.cpp -o obj/project_test.o

obj/sstring_test.o: tests/sstring_test.cpp
	$(CC) $(CFLAGS) -c tests/sstring_test.cpp -o obj/sstring_test.o

obj/sstring.o: src/sstring.cpp
	$(CC) $(CFLAGS) -c src/sstring.cpp -o obj/sstring.o

obj/category.o: src/category.cpp
	$(CC) $(CFLAGS) -c src/category.cpp -o obj/category.o

obj/project.o: src/project.cpp
	$(CC) $(CFLAGS) -c src/project.cpp -o obj/project.o

obj/list_test.o: tests/list_test.cpp
	$(CC) $(CFLAGS) -c tests/list_test.cpp -o obj/list_test.o

obj/linked_list.o: src/linked_list.cpp
	$(CC) $(CFLAGS) -c src/linked_list.cpp -o obj/linked_list.o

TESTS_MAIN: $(TESTS_SRC)
	$(CC) $(CFLAGS) -c $(TESTS_SRC) -o $(TESTS_MAIN)
