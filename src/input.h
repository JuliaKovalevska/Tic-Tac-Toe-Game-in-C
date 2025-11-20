#ifndef INPUT_H
#define INPUT_H

int input_read_board_size(void);
char input_read_player_symbol(void);
int input_read_move(int* row, int* col, int board_size);

#endif