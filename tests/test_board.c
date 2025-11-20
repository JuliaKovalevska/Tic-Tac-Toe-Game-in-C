#include <stdio.h>
#include <assert.h>
#include "board.h"

void test_board_init() {
    Board board;
    board_init(&board, 5);
    
    assert(board.size == 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            assert(board.cells[i][j] == ' ');
        }
    }
    printf("✓ test_board_init passed\n");
}

void test_board_set_and_is_empty() {
    Board board;
    board_init(&board, 5);
    
    assert(board_is_empty(&board, 0, 0) == 1);
    board_set(&board, 0, 0, 'X');
    assert(board_is_empty(&board, 0, 0) == 0);
    assert(board.cells[0][0] == 'X');
    
    printf("✓ test_board_set_and_is_empty passed\n");
}
void test_board_is_full() {
    Board board;
    board_init(&board, 5);
    
    assert(board_is_full(&board) == 0);
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board_set(&board, i, j, 'X');
        }
    }
    
    assert(board_is_full(&board) == 1);
    printf("✓ test_board_is_full passed\n");
}

void test_board_partial_full() {
    Board board;
    board_init(&board, 5);
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            board_set(&board, i, j, 'O');
        }
    }
    
    assert(board_is_full(&board) == 0);
    board_set(&board, 0, 4, 'X');
    board_set(&board, 1, 4, 'X');
    board_set(&board, 2, 4, 'X');
    board_set(&board, 3, 4, 'X');
    assert(board_is_full(&board) == 0);
    board_set(&board, 4, 4, 'X');
    assert(board_is_full(&board) == 1);
    
    printf("✓ test_board_partial_full passed\n");
}

void run_board_tests() {
    printf("\n=== Board Tests ===\n");
    test_board_init();
    test_board_set_and_is_empty();
    test_board_is_full();
    test_board_partial_full();
}