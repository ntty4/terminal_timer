#ifndef OUTPUT_SCREEN_H
#define OUTPUT_SCREEN_H

#include "../header/globals.h"

struct coord {
    int x;
    int y;
};

typedef struct data_graphic {

    struct coord size_screen;
    struct coord rectLen;

} data_graphic;

typedef struct dynArr {
    int capacity;
    int size;
    char *arr;
} dynArr;

void dyAppend(dynArr *frame, int src_size, char *src);
void dyFree(dynArr *frame);
void printScreen(data_timer *dt, data_graphic *dg);
void printRect(dynArr *frame, data_graphic *dt, int col, int row);
#endif

