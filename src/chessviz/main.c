#include "board_read.h"
#include "print_board_stdout.h"
#include <libchessviz/move.h>
#include <stdio.h>
#define board_size 8
int main(int argc, char** argv)
{
    char board[board_size][board_size]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    int count = 1;
    print(*board);
    if (argc == 1) {
        printf("Введите количество ходов: ");
        scanf("%d", &count);
    } else {
        FILE* fp = fopen(argv[1], "r");
        while (!feof(fp)) {
            if (fgetc(fp) == '\n')
                count++;
        }
        --count;
        fclose(fp);
    }
    ok(board_read(argc, argv, count), count, *board);
    return 0;
}
