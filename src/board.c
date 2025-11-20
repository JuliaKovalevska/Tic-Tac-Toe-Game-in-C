#include "board.h"
#include <stdio.h>

void board_init(Board* board, int size) {
    board->size = size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board->cells[i][j] = ' ';
        }
    }
}

void board_print(const Board* board) {
    printf("\n   ");
    for (int i = 1; i <= board->size; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < board->size; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < board->size; j++) {
            printf(" %c ", board->cells[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int board_is_empty(const Board* board, int row, int col) {
    return board->cells[row][col] == ' ';
}

void board_set(Board* board, int row, int col, char symbol) {
    board->cells[row][col] = symbol;
}

int board_is_full(const Board* board) {
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (board->cells[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}