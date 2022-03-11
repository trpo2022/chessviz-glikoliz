CC=gcc
CFLAGS=-Wall -Werror
SOURCES=src/chessviz/*.c
all: board_read main run clean
board_read:
	$(CC) -c $(SOURCES)
main: board_read
	$(CC) $(CFLAGS) -o main *.o
run: main
	./main $(file)
clean:
	rm -rf *.o main
.PHONY: main clean