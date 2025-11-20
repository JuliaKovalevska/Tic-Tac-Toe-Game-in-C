#ifndef BOARD_H
#define BOARD_H

#define MAX_SIZE 10
#define MIN_SIZE 5

typedef struct {
    char cells[MAX_SIZE][MAX_SIZE];
    int size;
} Board;

void board_init(Board* board, int size);
void board_print(const Board* board);
int board_is_empty(const Board* board, int row, int col);
void board_set(Board* board, int row, int col, char symbol);
int board_is_full(const Board* board);

#endif