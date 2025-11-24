#ifndef GAME_H
#define GAME_H

#include "board.h"

void run_game();
int check_win(char** board, int size, int row, int col, char symbol);

#endif