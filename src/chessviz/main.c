#include "board_read.h"
#include "print_board_stdout.h"
#include <libchessviz/move.h>
#include <stdio.h>
#include <string.h>
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
    char** s;
    print(*board);
    if (argc == 1) {
        printf("Для выхода напишите quit.\n");
        while(strcmp((s=board_read(argc,argv,count))[0],"quit\n")!=0)
        {   
            ok(s, 1, *board);
            count++;
        }
    } else {
        FILE* fp = fopen(argv[1], "r");
        while (!feof(fp)) {
            if (fgetc(fp) == '\n')
                count++;
        }
        --count;
        fclose(fp);
        ok(board_read(argc, argv, count), count, *board);
    }
    return 0;
}
