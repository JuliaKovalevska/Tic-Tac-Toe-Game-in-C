#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "input.h"
#include "board.h"
#include "utils.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif

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

    if (symbol == 'X' || symbol == 'O') {
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
    #ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hStdin, &prev_mode);
    SetConsoleMode(hStdin, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;

    while (1) {
        double elapsed = difftime(time(NULL), start_time);
        double remaining = time_limit - elapsed;
        
        if (remaining <= 0) {
            SetConsoleMode(hStdin, prev_mode);
            return 0;
        }
        
        int min = (int)remaining / 60;
        int sec = (int)remaining % 60;
        
        printf("\rTime left: %02d:%02d | Click to move (Q to quit)    ", min, sec);
        fflush(stdout);
        
        DWORD num_events = 0;
        GetNumberOfConsoleInputEvents(hStdin, &num_events);

        if (num_events > 0) {
            ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);

            for (DWORD i = 0; i < cNumRead; i++) {
                
                if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                    char key = irInBuf[i].Event.KeyEvent.uChar.AsciiChar;
                    if (key == 'q' || key == 'Q' || irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                        SetConsoleMode(hStdin, prev_mode);
                        exit(0);
                    }
                }

                if (irInBuf[i].EventType == MOUSE_EVENT) {
                    MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;
                    
                    if (mer.dwEventFlags == MOUSE_MOVED) {
                        continue;
                    }

                    if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                        int mouseX = mer.dwMousePosition.X;
                        int mouseY = mer.dwMousePosition.Y;

                        int r = mouseY - 2; 
                        int c = (mouseX - 3) / 3;

                        if (r >= 0 && r < size && c >= 0 && c < size) {
                            if (mouseX >= 3) {
                                *row = r;
                                *col = c;
                                SetConsoleMode(hStdin, prev_mode);
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        Sleep(50);
    }
    #else
    enable_mouse_input();
    
    while(1) {
        double elapsed = difftime(time(NULL), start_time);
        double remaining = time_limit - elapsed;
        
        if (remaining <= 0) {
            disable_mouse_input();
            return 0;
        }

        int min = (int)remaining / 60;
        int sec = (int)remaining % 60;
        
        printf("\rTime left: %02d:%02d | Click to move (Q to quit)    ", min, sec);
        fflush(stdout);

        fd_set set;
        struct timeval timeout;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; 

        int rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

        if (rv > 0) {
            unsigned char buf[6];
            if (read(STDIN_FILENO, buf, 1) > 0) {
                if (buf[0] == 'q' || buf[0] == 'Q') {
                    disable_mouse_input();
                    exit(0);
                }

                if (buf[0] == 0x1B) {
                    if (read(STDIN_FILENO, buf, 1) > 0 && buf[0] == '[') {
                        if (read(STDIN_FILENO, buf, 1) > 0 && buf[0] == 'M') {
                            read(STDIN_FILENO, &buf[3], 3); 
                            
                            int button = buf[3] - 32;
                            int x = buf[4] - 33; 
                            int y = buf[5] - 33; 

                            if (button == 0) { 
                                int r = y - 1; 
                                int c = (x - 3) / 3;

                                if (r >= 0 && r < size && c >= 0 && c < size) {
                                    if (x >= 3) {
                                        *row = r;
                                        *col = c;
                                        disable_mouse_input();
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    #endif
}