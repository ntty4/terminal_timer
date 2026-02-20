CC = gcc
SRC = src/terminal.c src/time_logic.c src/game_exit.c src/output_screen.c src/main.c src/input_key.c
CFLAGS = -Wall -Werror -Wextra -g

make:
	$(CC) $(CFLAGS) $(SRC) -o main

exec:
	$(CC) $(CFLAGS) $(SRC) -o main && ./main

clean:
	rm main
