#include "../header/output_screen.h"
#include "../header/game_exit.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>





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

            else if((x == 0 && y == 0) || (x == 0 && y == row-1) || (x == col-1 && y == 0) || (x == col-1 && y == row-1)) {
                el = '+';
            }
            else continue;
            len = snprintf(buff, 64, "\x1b[%d;%dH%c", y+y_offset, x+x_offset, el);
            dyAppend(frame, len, buff);
        }
    }
}

static void numAppender(dynArr *frame, char num, int numOffset, int y_offset) {
    if (num < '0' || num > ':') return;

    /* in this part the idea is to map every character to a specific position
     * in the array, so that in digit_patterns[0] -> his representation of 0.
     *
     * static -> it is only in this file, not outside
     * const -> cannot be modified */
    const uint16_t digit_patterns[] = {
        0x7B6F, // 111 101 101 101 111
        0x2492, // 010 010 010 010 010
        0x73E7, // 111 001 111 100 111
        0x73CF, // 111 001 111 001 111
        0x5BC9, // 101 101 111 001 001
        0x79CF, // 111 100 111 001 111
        0x79EF, // 111 100 111 101 111
        0x7249, // 111 001 010 010 010
        0x7BEF, // 111 101 111 101 111
        0x7Bcf, // 111 101 111 001 111
        0x410   // 000 010 000 010 000
    };

    /* there i am turning the char into its numerical representation 
     * and them mapping this number to its bit mask */
    uint16_t pattern = digit_patterns[num - '0'];
    char buff[32];

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 3; x++) {

            /* the idea is to caluclate in which position should i check for see if 
             * put or not puth the character:
             *
             * I know that there are 15 cells, (0-14), and are 3 row * 5 line, 0 index
             * based, so i can multiply the row index by 3 and sum the column position;
             * in this way i obtain what bit i should check */
            int bitPosToCheck = 14 - (y * 3 + x);

            /* Naw that i know in which posotion is the bit to be checked, i move that bit
             * on the left '>>' unitl it becomes the first; and after that i check with '&1'
             * if i must or not print it */
            if ((pattern >> bitPosToCheck) & 1) {
                int len = snprintf(buff, sizeof(buff), "\x1b[%d;%dH%s", 
                                   y_offset + y + 1, numOffset + x + 1, "\u2588");
                dyAppend(frame, len, buff);
            }
        }
    }
}

void time2screen(dynArr *frame, data_timer *dt, data_graphic *dg) {
    char strTime[64];
    int len;
    int x_offset = (dg->size_screen.x - dg->rectLen.x) / 2;
    int y_offset = (dg->size_screen.y - dg->rectLen.y) / 2;

    len = snprintf(strTime, sizeof(strTime), "%02d:%02d:%02d", dt->hrs, dt->min, dt->sec);

    for(int idx = 0; idx < len; idx++) {
        numAppender(frame, strTime[idx], x_offset + idx * 4, y_offset);
    }
}

void printScreen(data_timer *dt, data_graphic *dg) {
    dynArr frame = {0, 0, NULL};

    dyAppend(&frame, 4, "\x1b[2J");
    time2screen(&frame, dt, dg);

    write(STDOUT_FILENO, frame.arr, frame.size);
    dyFree(&frame);
}
