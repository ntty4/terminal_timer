#include "../header/input_key.h"
#include "../header/output_screen.h"
#include "../header/terminal.h"
#include "../header/game_exit.h"
#include "../header/globals.h"
#include "../header/time_logic.h"

#include <stdio.h>
#include <unistd.h>
#include <time.h>

data_timer dt;
data_graphic dg;

void initTimer(int seconds, int minutes, int hours) {
    dt.sec = seconds;
    dt.min = minutes;
    dt.hrs = hours;

    dt.tim.tv_sec = 0;
    dt.tim.tv_nsec = 5000000L;

    dg.rectLen.x = 30;
    dg.rectLen.y = 5;
}


int main(void) {
    getTerminalSize(&dg.size_screen.x, &dg.size_screen.y);
    terminalRaw();
    cleanScreen();
    initTimer(50, 59, 2);
    for(;;) {
        rawInput();
        timer(&dt);
        printScreen(&dt, &dg);
        nanosleep(&dt.tim, NULL);
    }

}
