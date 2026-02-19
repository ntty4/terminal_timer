#ifndef GLOBALS_H
#define GLOBALS_H

#include <time.h>

typedef struct data_timer {
    int hrs;
    int min;
    int sec;

    struct timespec tim;

} data_timer;

#endif
