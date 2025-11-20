#include "utils.h"
#include <stdio.h>

void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[2J\033[H");
    #endif
}