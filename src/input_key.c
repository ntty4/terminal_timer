#include "../header/input_key.h"
#include "../header/game_exit.h"

#include <unistd.h>
#include <errno.h>

void rawInput(void) {
    char c;
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");

    switch (c) {
        case 'q': exitGame();
    }
}
