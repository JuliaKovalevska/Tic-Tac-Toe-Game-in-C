#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");
    #endif
}

#ifndef _WIN32
struct termios orig_termios;

void reset_terminal_mode() {
    tcsetattr(0, TCSANOW, &orig_termios);
    printf("\033[?1000l"); 
    printf("\033[?25h");   
}

void set_conio_terminal_mode() {
    struct termios new_termios;
    tcgetattr(0, &orig_termios);
    atexit(reset_terminal_mode); 
    
    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(0, TCSANOW, &new_termios);
}
#endif

void enable_mouse_input() {
    #ifdef _WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    #else
        set_conio_terminal_mode();
        printf("\033[?1000h"); 
        printf("\033[?25l");   
        fflush(stdout);
    #endif
}

void disable_mouse_input() {
    #ifdef _WIN32
       
    #else
        reset_terminal_mode();
    #endif
}