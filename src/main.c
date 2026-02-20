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

    dt.tim.tv_sec = 1;
    dt.tim.tv_nsec = 0;

    dg.rectLen.x = 30;
    dg.rectLen.y = 5;

    write(STDOUT_FILENO, "\x1b[?25l", 6);
}


int main(void) {
    getTerminalSize(&dg.size_screen.x, &dg.size_screen.y);
    terminalRaw();
    cleanScreen();
    initTimer(0, 0, 0);
    for(;;) {
        rawInput();
        stopWatch(&dt);
        printScreen(&dt, &dg);
        nanosleep(&dt.tim, NULL);
    }

}
