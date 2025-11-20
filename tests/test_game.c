#include <stdio.h>
#include <assert.h>
#include "game.h"

void test_game_init() {
    Game game;
    game_init(&game, 5, 'X');
    
    assert(game.board.size == 5);
    assert(game.player1.symbol == 'X');
    assert(game.player2.symbol == 'O');
    assert(game.player1.id == 1);
    assert(game.player2.id == 2);
    assert(game.current_player == &game.player1);
    
    printf("✓ test_game_init passed\n");
}

void test_game_init_o_first() {
    Game game;
    game_init(&game, 7, 'O');
    
    assert(game.player1.symbol == 'O');
    assert(game.player2.symbol == 'X');
    assert(game.current_player == &game.player2);
    
    printf("✓ test_game_init_o_first passed\n");
}

void test_game_switch_player() {
    Game game;
    game_init(&game, 5, 'X');
    
    assert(game.current_player == &game.player1);
    game_switch_player(&game);
    assert(game.current_player == &game.player2);
    game_switch_player(&game);
    assert(game.current_player == &game.player1);
    
    printf("✓ test_game_switch_player passed\n");
}

void test_game_horizontal_win() {
    Game game;
    game_init(&game, 5, 'X');
    
    board_set(&game.board, 0, 0, 'X');
    board_set(&game.board, 0, 1, 'X');
    board_set(&game.board, 0, 2, 'X');
    board_set(&game.board, 0, 3, 'X');
    
    assert(game_check_win(&game, 0, 3) == 0);
    
    board_set(&game.board, 0, 4, 'X');
    assert(game_check_win(&game, 0, 4) == 1);
    
    printf("✓ test_game_horizontal_win passed\n");
}

void test_game_vertical_win() {
    Game game;
    game_init(&game, 5, 'X');
    
    board_set(&game.board, 0, 2, 'O');
    board_set(&game.board, 1, 2, 'O');
    board_set(&game.board, 2, 2, 'O');
    board_set(&game.board, 3, 2, 'O');
    board_set(&game.board, 4, 2, 'O');
    
    assert(game_check_win(&game, 4, 2) == 1);
    
    printf("✓ test_game_vertical_win passed\n");
}

void test_game_diagonal_win() {
    Game game;
    game_init(&game, 6, 'X');
    
    board_set(&game.board, 0, 0, 'X');
    board_set(&game.board, 1, 1, 'X');
    board_set(&game.board, 2, 2, 'X');
    board_set(&game.board, 3, 3, 'X');
    board_set(&game.board, 4, 4, 'X');
    
    assert(game_check_win(&game, 2, 2) == 1);
    
    printf("✓ test_game_diagonal_win passed\n");
}

void test_game_antidiagonal_win() {
    Game game;
    game_init(&game, 7, 'O');
    
    board_set(&game.board, 0, 6, 'O');
    board_set(&game.board, 1, 5, 'O');
    board_set(&game.board, 2, 4, 'O');
    board_set(&game.board, 3, 3, 'O');
    board_set(&game.board, 4, 2, 'O');
    
    assert(game_check_win(&game, 3, 3) == 1);
    
    printf("✓ test_game_antidiagonal_win passed\n");
}

void test_game_no_win_four_in_row() {
    Game game;
    game_init(&game, 5, 'X');
    
    board_set(&game.board, 1, 0, 'X');
    board_set(&game.board, 1, 1, 'X');
    board_set(&game.board, 1, 2, 'X');
    board_set(&game.board, 1, 3, 'X');
    
    assert(game_check_win(&game, 1, 3) == 0);
    
    printf("✓ test_game_no_win_four_in_row passed\n");
}

void test_game_win_six_in_row() {
    Game game;
    game_init(&game, 8, 'X');
    
    for (int i = 0; i < 6; i++) {
        board_set(&game.board, 3, i, 'X');
    }
    
    assert(game_check_win(&game, 3, 5) == 1);
    assert(game_check_win(&game, 3, 2) == 1);
    
    printf("✓ test_game_win_six_in_row passed\n");
}

void test_game_win_middle_placement() {
    Game game;
    game_init(&game, 7, 'O');
    
    board_set(&game.board, 2, 1, 'O');
    board_set(&game.board, 2, 2, 'O');
    board_set(&game.board, 2, 4, 'O');
    board_set(&game.board, 2, 5, 'O');
    
    assert(game_check_win(&game, 2, 4) == 0);
    
    board_set(&game.board, 2, 3, 'O');
    assert(game_check_win(&game, 2, 3) == 1);
    
    printf("✓ test_game_win_middle_placement passed\n");
}

void test_game_blocked_sequence() {
    Game game;
    game_init(&game, 6, 'X');
    
    board_set(&game.board, 0, 0, 'X');
    board_set(&game.board, 0, 1, 'X');
    board_set(&game.board, 0, 2, 'O');
    board_set(&game.board, 0, 3, 'X');
    board_set(&game.board, 0, 4, 'X');
    
    assert(game_check_win(&game, 0, 4) == 0);
    
    printf("✓ test_game_blocked_sequence passed\n");
}

void run_game_tests() {
    printf("\n=== Game Tests ===\n");
    test_game_init();
    test_game_init_o_first();
    test_game_switch_player();
    test_game_horizontal_win();
    test_game_vertical_win();
    test_game_diagonal_win();
    test_game_antidiagonal_win();
    test_game_no_win_four_in_row();
    test_game_win_six_in_row();
    test_game_win_middle_placement();
    test_game_blocked_sequence();
}