#include "input.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int input_read_board_size(void) {
    char buffer[100];
    int size;
    
    while (1) {
        printf("Enter the board size (5–10): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }
        
        if (sscanf(buffer, "%d", &size) == 1) {
            if (size >= MIN_SIZE && size <= MAX_SIZE) {
                return size;
            }
        }
        printf("Invalid input. Please enter a number between 5 and 10.\n");
    }
}

char input_read_player_symbol(void) {
    char buffer[100];
    
    printf("Which side are you playing? (X/O) — or press Enter for X: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 'X';
    }
    
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '\n') {
            return 'X';
        }
        if (isalpha(buffer[i])) {
            char c = toupper(buffer[i]);
            if (c == 'X' || c == 'O') {
                return c;
            }
        }
    }
    
    return 'X';
}

int input_read_move(int* row, int* col, int board_size) {
    char buffer[100];
    int r, c;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    if (sscanf(buffer, "%d %d", &r, &c) != 2) {
        return 0;
    }
    
    if (r < 1 || r > board_size || c < 1 || c > board_size) {
        printf("Invalid coordinates. Enter numbers in the range 1..%d.\n", board_size);
        return 0;
    }
    
    *row = r - 1;
    *col = c - 1;
    return 1;
}