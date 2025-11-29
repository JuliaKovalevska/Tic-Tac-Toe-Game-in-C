CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

GAME_OBJS = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

ifeq ($(OS),Windows_NT)
    TARGET = $(BIN_DIR)/game.exe
    TEST_TARGET = $(BIN_DIR)/test_game.exe
else
    TARGET = $(BIN_DIR)/game
    TEST_TARGET = $(BIN_DIR)/test_game
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(GAME_OBJS) $(OBJ_DIR)/test_main.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/test_main.o: $(TEST_DIR)/test_main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean test