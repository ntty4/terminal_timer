#include "../header/globals.h"
#include <stdlib.h>

void stopWatch(data_timer *dt) {
    dt->sec += 1;

    if(dt -> sec == 60) {
        dt-> sec = 0;
        dt -> min += 1;

        if (dt -> min == 60) {
            dt -> min = 0;
            dt -> hrs += 1;
        }
    }
}

void timer(data_timer *dt) {
    if (dt->sec == 0 && dt -> min != 0) {
        dt->min -= 1;
        dt-> sec = 60;

        if(dt -> min == 0 && dt -> hrs != 0) {
            dt -> hrs -= 1;
            dt -> min = 60;
        }
    }

    if (dt -> sec == 0 && dt -> min == 0 && dt -> hrs == 0) exit(0);

    dt -> sec -= 1;
}
