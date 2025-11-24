#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/board.h"
#include "../src/game.h"

void test_board_creation() {
    printf("Testing board creation...\n");
    int size = 10;
    char** board = create_board(size);
    assert(board != NULL);
    init_board(board, size);
    
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            assert(board[i][j] == ' ');
        }
    }
    free_board(board, size);
    printf("Board creation passed.\n");
}

void test_set_cell() {
    printf("Testing set_cell...\n");
    int size = 5;
    char** board = create_board(size);
    init_board(board, size);
    
    assert(is_cell_empty(board, 0, 0) == 1);
    set_cell(board, 0, 0, 'X');
    assert(is_cell_empty(board, 0, 0) == 0);
    assert(board[0][0] == 'X');
    
    free_board(board, size);
    printf("set_cell passed.\n");
}

void test_win_horizontal() {
    printf("Testing horizontal win...\n");
    int size = 10;
    char** board = create_board(size);
    init_board(board, size);
    
    for(int i=0; i<5; i++) {
        set_cell(board, 0, i, 'X');
    }
    
    assert(check_win(board, size, 0, 4, 'X') == 1);
    
    free_board(board, size);
    printf("Horizontal win passed.\n");
}

void test_win_vertical() {
    printf("Testing vertical win...\n");
    int size = 10;
    char** board = create_board(size);
    init_board(board, size);
    
    for(int i=0; i<5; i++) {
        set_cell(board, i, 0, 'O');
    }
    
    assert(check_win(board, size, 4, 0, 'O') == 1);
    
    free_board(board, size);
    printf("Vertical win passed.\n");
}

void test_win_diagonal() {
    printf("Testing diagonal win...\n");
    int size = 10;
    char** board = create_board(size);
    init_board(board, size);
    
    for(int i=0; i<5; i++) {
        set_cell(board, i, i, 'X');
    }
    
    assert(check_win(board, size, 4, 4, 'X') == 1);
    
    free_board(board, size);
    printf("Diagonal win passed.\n");
}

void test_win_anti_diagonal() {
    printf("Testing anti-diagonal win...\n");
    int size = 10;
    char** board = create_board(size);
    init_board(board, size);
    
    for(int i=0; i<5; i++) {
        set_cell(board, i, 4-i, 'O');
    }
    
    assert(check_win(board, size, 4, 0, 'O') == 1);
    
    free_board(board, size);
    printf("Anti-diagonal win passed.\n");
}

void test_no_win() {
    printf("Testing no win...\n");
    int size = 10;
    char** board = create_board(size);
    init_board(board, size);
    
    for(int i=0; i<4; i++) {
        set_cell(board, 0, i, 'X');
    }
    
    assert(check_win(board, size, 0, 3, 'X') == 0);
    
    free_board(board, size);
    printf("No win passed.\n");
}

int main() {
    test_board_creation();
    test_set_cell();
    test_win_horizontal();
    test_win_vertical();
    test_win_diagonal();
    test_win_anti_diagonal();
    test_no_win();
    
    printf("All tests passed!\n");
    return 0;
}
