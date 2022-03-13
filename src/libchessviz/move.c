#include <chessviz/print_board_stdout.h>
#include <stdio.h>
#include <stdlib.h>
#define board_size 8
int char_to_int(char letter)
{
    switch (letter) {
    case 'a':
        return 0;
    case 'b':
        return 1;
    case 'c':
        return 2;
    case 'd':
        return 3;
    case 'e':
        return 4;
    case 'f':
        return 5;
    case 'g':
        return 6;
    case 'h':
        return 7;
    default:
        return -1;
    }
}
struct move_info {
    int fmx;  // first-move-x
    int fmy;  // first-move-y
    int smx;  // sec-move-x
    int smy;  // sec-move-y
    char act; // action
} m;
void quiet_move(
        int x1, int y1, int x2, int y2, char board[board_size][board_size])
{
    char temp = board[y1][x1];
    board[y1][x1] = board[y2][x2];
    board[y2][x2] = temp;
}
void take_figure_move(
        int x1, int y1, int x2, int y2, char board[board_size][board_size])
{
    board[y2][x2] = board[y1][x1];
    board[y1][x1] = ' ';
}
void move_pawn(
        int x1,
        int y1,
        int x2,
        int y2,
        char board[board_size][board_size],
        char action)
{
    if (x1 == x2 && action == '-') {
        if (board[y2][x2] == ' ') {
            if (abs(y1 - y2) == 1)
                quiet_move(x1, y1, x2, y2, board);
            if (abs(y1 - y2) == 2) {
                if (y1 == 6 && board[y1][x1] == 'P'
                    && board[y2 + 1][x2] == ' ') // black
                    quiet_move(x1, y1, x2, y2, board);
                if (y1 == 1 && board[y1][x1] == 'p'
                    && board[y2 - 1][x2] == ' ') // white
                    quiet_move(x1, y1, x2, y2, board);
            }
        }
    }
    if (abs(x1 - x2) == 1 && abs(y1 - y2) == 1 && action == 'x')
        if (board[y2][x2] != ' ')
            take_figure_move(x1, y1, x2, y2, board);
    print(*board);
}
void ok(char** s, int count, char board[board_size][board_size])
{
    int j = 0, check = 0;
    char figure;
    for (int i = 0; i < count; i++) {
        while (s[i][j] != '\n') {
            if (check == 1) {
                if (char_to_int(s[i][j]) != -1) {
                    figure = s[i][j - 1];
                    m.fmx = char_to_int(s[i][j]);
                    m.fmy = 8 - (s[i][j + 1] - '0');
                    m.act = s[i][j + 2];
                    m.smx = char_to_int(s[i][j + 3]);
                    m.smy = 8 - (s[i][j + 4] - '0');
                    // printf("j=%d\t i=%d\ny: %d x: %d - y: %d x: %d\nfigure=
                    // /%c/\n", j, i, m.fmy, m.fmx, m.smy, m.smx, figure);
                    // printf("%c - %c\n", board[m.fmy][m.fmx],
                    // board[m.smy][m.smx]);
                    if (figure == ' ')
                        move_pawn(m.fmx, m.fmy, m.smx, m.smy, board, m.act);
                    j = j + 3;
                }
            }
            if (s[i][j] == ' ')
                check = 1;
            j++;
        }
        printf("\n");
        check = 0;
        j = 0;
    }
}