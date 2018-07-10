# File: makefile
# Description: Basic makefile for automated buidls
CC := g++
CFLAGS := -std=c++98 -Wall -g -I ../third_party/ -I include -I src
INCLUDE := -I ../third_party/ -I include -I src

SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
APPLICATION := main.cpp
TARGET := obj/debug/main 

TEST_DIR := tests
TEST_OBJ := tests/obj
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp,$(TEST_OBJ)/%.o,$(TEST_SRCS))
tests := tests/obj/debug/run_tests

TESTS_MAIN := ../third_party/tests_main.o
THIRD_PARTY := ../third_party/tests_main.cpp

TARGET: $(OBJ_FILES) $(APPLICATION)
	$(CC) $(CFLAGS) -o $(TARGET) $^

tests: $(TEST_OBJS) $(OBJ_FILES) $(TESTS_MAIN)
	$(CC) $(CFLAGS) -o $(tests) $^

$(TEST_OBJ)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

TESTS_MAIN: $(THIRD_PARTY)
	$(CC) $(CFLAGS) -c $(THIRD_PARTY) -o $(TESTS_MAIN)

.PHONEY: clean

clean:
	rm $(OBJ_DIR)/*.o
	rm $(TARGET)
	rm $(TEST_OBJ)/*.o
	rm $(TESTS_MAIN)
	rm $(tests)
