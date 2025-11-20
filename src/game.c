#include "game.h"
#include <stdio.h>

void game_init(Game* game, int board_size, char p1_symbol) {
    board_init(&game->board, board_size);
    
    game->player1.id = 1;
    game->player1.symbol = p1_symbol;
    
    game->player2.id = 2;
    game->player2.symbol = (p1_symbol == 'X') ? 'O' : 'X';
    
    game->current_player = (p1_symbol == 'X') ? &game->player1 : &game->player2;
}

static int count_direction(const Board* board, int row, int col, char symbol, int dr, int dc) {
    int count = 0;
    int r = row + dr;
    int c = col + dc;
    
    while (r >= 0 && r < board->size && c >= 0 && c < board->size && 
           board->cells[r][c] == symbol) {
        count++;
        r += dr;
        c += dc;
    }
    
    return count;
}

int game_check_win(const Game* game, int row, int col) {
    char symbol = game->board.cells[row][col];
    
    int directions[4][2] = {
        {0, 1},   // horizontal
        {1, 0},   // vertical
        {1, 1},   // diagonal \
        {1, -1}   // diagonal /
    };
    
    for (int d = 0; d < 4; d++) {
        int dr = directions[d][0];
        int dc = directions[d][1];
        
        int count = 1;
        count += count_direction(&game->board, row, col, symbol, dr, dc);
        count += count_direction(&game->board, row, col, symbol, -dr, -dc);
        
        if (count >= 5) {
            return 1;
        }
    }
    
    return 0;
}

void game_switch_player(Game* game) {
    if (game->current_player == &game->player1) {
        game->current_player = &game->player2;
    } else {
        game->current_player = &game->player1;
    }
}

Player* game_get_current_player(const Game* game) {
    return game->current_player;
}