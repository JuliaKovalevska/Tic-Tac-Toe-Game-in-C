#ifndef INPUT_H
#define INPUT_H

#include <time.h>

int get_board_size();
char get_player_symbol();
int get_move_coordinates(int size, int *row, int *col, time_t start_time, double time_limit);

#endif 