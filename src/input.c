#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "input.h"
#include "board.h"
#include "utils.h"

int get_board_size() {
    int size;
    while (1) {
        printf("Enter the board size (min 5): ");
        if (scanf("%d", &size) == 1) {
            clear_input_buffer();
            if (size >= MIN_SIZE) {
                return size;
            }
        } else {
            clear_input_buffer();
        }
        printf("Invalid input. Please enter a number >= 5.\n");
    }
}

char get_player_symbol() {
    char symbol;
    printf("Which side are you playing? (X/O) - or press Enter for X: ");
    
    int c = getchar();
    if (c == '\n') {
        return 'X';
    }
    
    symbol = toupper(c);
    if (c != '\n') {
        clear_input_buffer();
    }

    if (symbol == 'X'  symbol == 'O') {
        return symbol;
    }
    
    while (symbol != 'X' && symbol != 'O') {
        printf("Invalid symbol. Please enter X or O (or press Enter for X): ");
        c = getchar();
        if (c == '\n') {
            return 'X';
        }
        symbol = toupper(c);
        if (c != '\n') clear_input_buffer();
    }
    return symbol;
}

int get_move_coordinates(int size, int *row, int *col, time_t start_time, double time_limit) {
    char buffer[256] = {0};
    int index = 0;
    
    while (1) {
        double elapsed = difftime(time(NULL), start_time);
        double remaining = time_limit - elapsed;
        
        if (remaining <= 0) {
            return 0;
        }
        
        int min = (int)remaining / 60;
        int sec = (int)remaining % 60;
        
        printf("\rTime left: %02d:%02d | Enter row col: %s   ", min, sec, buffer);
        fflush(stdout);
        
        if (_kbhit()) {
            int ch = _getch();
            
            if (ch == '\r'  ch == '\n') {
                printf("\n");
                
                int r, c;
                if (sscanf(buffer, "%d %d", &r, &c) == 2) {
                    if (r >= 1 && r <= size && c >= 1 && c <= size) {
                        *row = r - 1;
                        *col = c - 1;
                        return 1;
                    } else {
                        printf("Invalid coordinates. Range is 1..%d.\n", size);
                    }
                } else {
                    printf("Invalid format. Use: row col (e.g. 1 2)\n");
                }
                
                memset(buffer, 0, sizeof(buffer));
                index = 0;
                
            } else if (ch == '\b' || ch == 127) {
                if (index > 0) {
                    buffer[--index] = '\0';
                    printf("\rTime left: %02d:%02d | Enter row col: %s   ", min, sec, buffer);
                }
            } else if (isprint(ch)) {
                if (index < (int)(sizeof(buffer) - 1)) {
                    buffer[index++] = (char)ch;
                    buffer[index] = '\0';
                }
            }
        }
        
        Sleep(100);
    }
}