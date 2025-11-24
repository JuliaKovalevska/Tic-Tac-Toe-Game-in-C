#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "board.h"
#include "input.h"

int check_direction(char** board, int size, int row, int col, int dRow, int dCol, char symbol) {
    int count = 0;
    for (int i = 1; i < 5; i++) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        if (r >= 0 && r < size && c >= 0 && c < size && board[r][c] == symbol) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        int r = row - i * dRow;
        int c = col - i * dCol;
        if (r >= 0 && r < size && c >= 0 && c < size && board[r][c] == symbol) {
            count++;
        } else {
            break;
        }
    }
    return count + 1;
}

int check_win(char** board, int size, int row, int col, char symbol) {
    if (check_direction(board, size, row, col, 0, 1, symbol) >= 5) return 1;
    if (check_direction(board, size, row, col, 1, 0, symbol) >= 5) return 1;
    if (check_direction(board, size, row, col, 1, 1, symbol) >= 5) return 1;
    if (check_direction(board, size, row, col, 1, -1, symbol) >= 5) return 1;
    
    return 0;
}

void run_game() {
    int size = get_board_size();
    char** board = create_board(size);
    
    char p1_symbol = get_player_symbol();
    char p2_symbol = (p1_symbol == 'X') ? 'O' : 'X';
    
    printf("Player 2 is automatically assigned %c.\n", p2_symbol);
    
    init_board(board, size);
    
    char current_symbol = 'X'; 
    
    int row, col;
    int winner = 0;
    
    time_t start_time = time(NULL);
    double time_limit = 300.0;
    int time_up = 0;

    while (!winner && !is_board_full(board, size)) {
        if (difftime(time(NULL), start_time) >= time_limit) {
            time_up = 1;
            break;
        }

        print_board(board, size);
        
        int player_num = (current_symbol == p1_symbol) ? 1 : 2;
        printf("Player %d's turn (%c).\n", player_num, current_symbol);
        
        while (1) {
            if (!get_move_coordinates(size, &row, &col, start_time, time_limit)) {
                time_up = 1;
                break;
            }

            if (is_cell_empty(board, row, col)) {
                break;
            } else {
                printf("This cell is already occupied\n");
                printf("Player %d's turn (%c).\n", player_num, current_symbol);
            }
        }
        
        if (time_up) break;

        set_cell(board, row, col, current_symbol);
        
        if (check_win(board, size, row, col, current_symbol)) {
            winner = player_num;
        } else {
            current_symbol = (current_symbol == 'X') ? 'O' : 'X';
        }
    }
    
    print_board(board, size);
    
    if (time_up) {
        printf("\nTime is up! Game over.\n");
    } else if (winner) {
        char win_symbol = (winner == 1) ? p1_symbol : p2_symbol;
        printf("Player %d (%c) has won!\n", winner, win_symbol);
    } else {
        printf("Draw! The board is full.\n");
    }

    free_board(board, size);
}