#include <stdio.h>
#include <stdlib.h>
#include "board.h"

char** create_board(int size) {
    char** board = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        board[i] = (char*)malloc(size * sizeof(char));
    }
    return board;
}

void free_board(char** board, int size) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

void init_board(char** board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

void print_board(char** board, int size) {
    printf("   ");
    for (int j = 1; j <= size; j++) {
        printf(" %2d", j);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < size; j++) {
            printf("[%c]", board[i][j]);
        }
        printf("\n");
    }
}

int is_cell_empty(char** board, int row, int col) {
    return board[row][col] == ' ';
}

void set_cell(char** board, int row, int col, char symbol) {
    board[row][col] = symbol;
}

int is_board_full(char** board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}
