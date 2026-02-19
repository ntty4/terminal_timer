#include "../header/output_screen.h"
#include "../header/game_exit.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void dyAppend(dynArr *frame, int src_size, char *src) {
    int new_size = frame->size + src_size;
    int old_capacity = frame->capacity;

    while(new_size >= frame->capacity - 1) {
        frame -> capacity = (frame -> capacity == 0 ? 128: frame -> capacity * 2);  
    }

    if(old_capacity < frame -> capacity) {
        char *new_arr = realloc(frame->arr, frame->capacity * sizeof(char));

        if(new_arr == NULL) die("realloc");
        frame -> arr = new_arr;
    }

    memcpy(&frame->arr[frame->size], src, src_size);
    frame-> size += src_size;
    frame->arr[frame->size] = '\0';
}

void dyFree(dynArr *frame) {
    free(frame->arr);
    frame -> arr = NULL;
    frame -> capacity = 0;
    frame -> size = 0;
}

void printRect(dynArr *frame, data_graphic *dt, int col, int row) {
    int len;
    char el;
    char buff[64];

    int x_offset = (dt->size_screen.x - col) /2;
    int y_offset = (dt->size_screen.y - row) /2;

    for(int y = 0; y < row; y++) {
        for(int x = 0; x < col; x++) {
            if((y == 0 || y == row - 1 ) && (x > 0 && x < col-1)) {
                el = '-';
            }

            else if((x == 0 || x == col - 1) && (y > 0 && y < row-1)) {
                el = '|';
            }

            else if(x == 0 && y == 0 || x == 0 && y == row-1 || x == col-1 && y == 0 || x == col-1 && y == row-1) {
                el = '+';
            }
            else continue;

            len = snprintf(buff, 64, "\x1b[%d;%dH%c", y+y_offset, x+x_offset, el);
            dyAppend(frame, len, buff);
        }
    }
}

void printScreen(data_timer *dt, data_graphic *dg) {
    dynArr frame = {0, 0, NULL};
    char buff[128];
    int size;
     
    printRect(&frame, dg, dg->rectLen.x, dg->rectLen.y);

    size = snprintf(buff, 128, "\x1b[%d;%dH h: %d, m: %d, s: %d",
                    dg->size_screen.y/2, (dg->size_screen.x - 20)/2, dt->hrs, dt->min, dt->sec);
    dyAppend(&frame, size, buff);

    write(STDOUT_FILENO, frame.arr, frame.size);
    dyFree(&frame);
}
