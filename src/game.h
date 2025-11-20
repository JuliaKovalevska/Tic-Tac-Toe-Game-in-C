#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct {
    int id;
    char symbol;
} Player;

typedef struct {
    Board board;
    Player player1;
    Player player2;
    Player* current_player;
} Game;

void game_init(Game* game, int board_size, char p1_symbol);
int game_check_win(const Game* game, int row, int col);
void game_switch_player(Game* game);
Player* game_get_current_player(const Game* game);

#endif