CC=gcc -c
CFLAGS=-Wall -Werror
SOURCE=src/chessviz/
LIBSOURCE=src/libchessviz/
INCLUDEPATH=-I src
all: board_read print_board_stdout move main chessviz
board_read:
	$(CC) $(INCLUDEPATH) $(SOURCE)board_read.c
print_board_stdout:
	$(CC) $(INCLUDEPATH) $(SOURCE)print_board_stdout.c
move:
	$(CC) $(INCLUDEPATH) $(LIBSOURCE)move.c
main:
	$(CC) $(INCLUDEPATH) $(SOURCE)main.c
chessviz: board_read print_board_stdout move main
	gcc $(CFLAGS) $(INCLUDEPATH) -o chessviz *.o
run: chessviz
	./chessviz $(file)
clean:
	rm -rf *.o chessviz
.PHONY: chessviz clean