#ifndef BOARD_H
#define BOARD_H

#define MIN_SIZE 5

char** create_board(int size);
void free_board(char** board, int size);
void init_board(char** board, int size);
void print_board(char** board, int size);
int is_cell_empty(char** board, int row, int col);
void set_cell(char** board, int row, int col, char symbol);
int is_board_full(char** board, int size);

#endif