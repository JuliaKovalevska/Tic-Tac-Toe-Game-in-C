# Tic-Tac-Toe — Five in a Row (C)

Short
-----
Console game "Tic-Tac-Toe — Five in a Row" for two players, implemented in C. Players choose the board size (5–10). The board is numbered horizontally and vertically from 1 to N. Mode: player vs player. The winner is the first player to place 5 identical symbols in a row horizontally, vertically, or diagonally.

Purpose
-------
- Implement the "five in a row" game logic in a terminal application.
- Provide correct input validation and error handling.
- Build a readable and modular code architecture in C for testing and extension.

Requirements Review
-------------------
Functional requirements:
- Two human players.
- Before the game:
  - Ask for board size N (integer, 5..10). Rule: N must be at least 5 and at most 10. If the user enters a value out of range or an invalid format, the program asks again.
  - Ask Player 1 which symbol they play as (X/O). If nothing is entered (press Enter) — default is X.
  - If Player 1 chooses X, Player 2 automatically becomes O (and vice versa).
- Player who plays X goes first.
- The N×N board must be numbered by rows and columns 1..N.
- After each move the board is printed with numbering.
- Players enter coordinates (row and column) for their move in the format: two numbers separated by a space (for example, "4 5").
- If a cell is already occupied, show the message "This cell is already occupied" and prompt the player to enter a move again.
- Victory condition: 5 identical symbols in a row horizontally, vertically, or diagonally.
- After a win or a draw the game ends with an appropriate message.

Input/Output (what each player sees)
------------------------------------
Player 1:
- "Enter the board size (5–10): "
- "Which side are you playing? (X/O) — or press Enter for X: "

Player 2:
- After Player 1's choice, Player 2 automatically gets the opposite symbol:
  - e.g. "Player 2 is automatically assigned O."
- Afterwards Player 2 is only asked for move coordinates.

During the game (both players):
- The board is displayed with numbering 1..N.
- Player 1 move prompt: "Player 1's turn (X). Enter the row and column separated by a space:"
- Error messages:
  - If coordinates are out of range: "Invalid coordinates. Enter numbers in the range 1..N."
  - If the cell is occupied: "This cell is already occupied"
  (The above messages are exact user-facing texts; you may provide English equivalents in logs or developer notes.)
- After every valid move the updated board is printed.
- On victory: "Player <1|2> (<X|O>) has won!"
- On draw: "Draw! The board is full."

Game Flow
---------
1. Ask for board size N (strictly 5..10).
2. Player 1 chooses symbol (X/O) or presses Enter → X.
3. Automatically assign the opposite symbol to Player 2.
4. Initialize empty N×N board.
5. While there is no win or draw:
   - Print the board.
   - Prompt the current player for coordinates.
   - Validate input and check whether the cell is free.
   - Place the symbol and check for victory (5 in a row).
   - If victory → print result and end.
   - If no available moves → declare draw.
   - Switch current player.

Components
----------
- CLI (main.c) — user interaction, board printing, main game loop.
- Game Engine (game.c / game.h) — move logic, win and draw checks.
- Board (board.c / board.h) — board state and operations: set/is_empty/print.
- Input (input.c / input.h) — read and parse input.
- Utils (utils.c / utils.h) — helper functions.

Data
----
- Board: char board[10][10] (indices 0..N-1), empty cell — ' '.
- Player: id (1/2), symbol ('X'/'O').

Win check
---------
- After the last move check in 4 directions (horizontal, vertical, two diagonals).
- Count consecutive identical symbols in both directions; if the total (including the last move) >= 5 → win.

Third-party libraries and dependencies
-------------------------------------
- No third-party libraries — only standard headers: stdio.h, stdlib.h, string.h, ctype.h.

Project structure (files and functions)
---------------------------------------
- src/
  - main.c
  - game.c
  - board.c
  - input.c
  - utils.c
  - game.h, board.h, input.h, utils.h
- Makefile
- README.md

Edge cases
----------
- Board size N: if input <5 or >10 — the program asks for the size again (strict rule: N ∈ [5,10]).
- Invalid coordinate format — ask again.
- Attempt to place on an occupied cell — print "This cell is already occupied" and do not change turn.

Build and run
-------------
With Makefile:
```
$ make
$ ./bin/tictactoe
```