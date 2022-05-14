#include <ctype.h>
#include <libchessviz/print_board_stdout.h>
#include <stdio.h>
#include <stdlib.h>
#define board_size 8
#define info m.fmx, m.fmy, m.smx, m.smy, board, m.act
#define board_info                                                      \
    int x1, int y1, int x2, int y2, char board[board_size][board_size], \
            char action
#define min(x1, x2) ((x1 < x2) ? x1 : x2)
#define max(x1, x2) ((x1 > x2) ? x1 : x2)
#define move_input x1, y1, x2, y2, board
#define move_figure move_figures(x1, y1, x2, y2, board)
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
char turn(int x, int y, char board[board_size][board_size])
{
    if (isupper(board[y][x]))
        return 'w';
    else
        return 'b';
}
struct move_info {
    int fmx;  // first-move-x
    int fmy;  // first-move-y
    int smx;  // second-move-x
    int smy;  // second-move-y
    char act; // action
} m;
void move_figures(
        int x1, int y1, int x2, int y2, char board[board_size][board_size])
{
    board[y2][x2] = board[y1][x1];
    board[y1][x1] = ' ';
}
void move_pawn(board_info)
{
    char turn1 = turn(x1, y1, board);
    char turn2 = turn(x2, y2, board);
    if (x1 == x2 && action == '-') { //Тихий ход
        if (board[y2][x2] == ' ') {
            if (abs(y2 - y1) == 1) {
                if (y2 < y1 && turn1 == 'w') // white
                    move_figure;
                if (y2 > y1 && turn1 == 'b') // black
                    move_figure;
            }
            if (abs(y1 - y2) == 2) {
                if (y1 == 6 && turn1 == 'w'
                    && board[y2 + 1][x2] == ' ') // white
                    move_figure;
                if (y1 == 1 && turn1 == 'b'
                    && board[y2 - 1][x2] == ' ') // black
                    move_figure;
            }
        }
    }
    if (abs(x1 - x2) == 1 && abs(y1 - y2) == 1
        && action == 'x') //Взятие другой фигуры
        if (turn1 != turn2) {
            if (y2 > y1 && turn1 == 'b')
                move_figure;
            if (y2 < y1 && turn1 == 'w')
                move_figure;
        }
    print(*board);
}
void move_king(board_info)
{
    if (turn(x1, y1, board) != turn(x2, y2, board)) {
        if (action == '-' && board[y2][x2] == ' ') {
            if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {
                move_figure;
            }
        }
        if (action == 'x' && board[y2][x2] != ' ') {
            move_figure;
        }
    }
    print(*board);
}
void move_rook(board_info)
{
    int ok = 0;
    if (turn(x1, y1, board)
        != turn(x2, y2, board)) { //проверяет не ест ли своего
        if (y1 == y2) {
            for (int i = min(x1, x2); i <= max(x1, x2); i++) {
                if (board[y1][i] != ' ') {
                    if (i == x2 && action == 'x')
                        move_figure;
                    if (i != x1) {
                        ok = 1;
                        break;
                    }
                }
            }
            if (ok == 0)
                if (action == '-')
                    move_figure;
        }
        if (x1 == x2) {
            for (int i = min(y1, y2); i <= max(y1, y2); i++) {
                if (board[i][x1] != ' ') {
                    if (i == y2 && action == 'x')
                        move_figure;
                    if (i != y1) {
                        ok = 1;
                        break;
                    }
                }
            }
            if (ok == 0)
                if (action == '-')
                    move_figure;
        }
    }
    print(*board);
}
void move_knight(board_info)
{
    if (turn(x1, y1, board) != turn(x2, y2, board)) {
        if ((abs(x1 - x2) == 1 && abs(y1 - y2) == 2)
            || (abs(x1 - x2) == 2 && abs(y1 - y2) == 1)) {
            if (board[y2][x2] == ' ' && action == '-')
                move_figure;
            if (board[y2][x2] != ' ' && action == 'x')
                move_figure;
        }
    }
    
    print(*board);
}
void move_bishop(board_info)
{
    int yy = 0;
    int ok = 0;
    if (abs(x1 - x2) == abs(y1 - y2)) {
        yy = y1;
        if (x1 < x2) {
            if (y1 > y2) {
                for (int i = x1; i <= x2; i++) {
                    if (board[yy][i] != ' ') {
                        if(i==x2 && action=='x')
                            move_figure;
                        if(i!=x1)
                        {
                            ok = 1;
                            break;
                        }
                    }
                    yy--;
                }
            } else {
                for (int i = x1; i <= x2; i++) {
                    if (board[yy][i] != ' ') {
                        if(i==x2 && action=='x')
                            move_figure;
                        if(i!=x1)
                        {
                            ok = 1;
                            break;
                        }
                    }
                    yy++;
                }
            }
        } else {
            if (y1 > y2) {
                for (int i = x1; i <= x2; i--) {
                    if (board[yy][i] != ' ') {
                        if(i==x2 && action=='x')
                            move_figure;
                        if(i!=x1)
                        {
                            ok = 1;
                            break;
                        }
                    }
                    yy--;
                }
            } else {
                for (int i = x1; i <= x2; i--) {
                    if (board[yy][i] != ' ') {
                        if(i==x2 && action=='x')
                            move_figure;
                        if(i!=x1)
                        {
                            ok = 1;
                            break;
                        }
                    }
                    yy++;
                }
            }
        }
        // yy=y1;
        // if(y1>y2)
        // {
        //     for(int i=(max(x1,x2));i>=(min(x1,x2));i--)
        //     {
        //         printf("yy=%d ; i=%d ; board[yy][i]=%c\n", yy, i,
        //         board[yy][i]); if(board[yy][i]!=' ')
        //         {
        //             if(i!=x1)
        //             {
        //                 ok=1;
        //                 break;
        //             }
        //             if(i==x2 && action=='x')
        //                 move_figure;
        //         }
        //         yy--;
        //     }
        // }
        // else
        // {
        //     for(int i=(min(x1,x2));i<=(max(x1,x2));i++)
        //     {
        //         printf("yy=%d ; i=%d ; board[yy][i]=%c\n", yy, i,
        //         board[yy][i]); if(board[yy][i]!=' ')
        //         {
        //             if(i!=x1)
        //             {
        //                 ok=1;
        //                 break;
        //             }
        //             if(i==x2 && action=='x')
        //                 move_figure;
        //         }
        //         yy--;
        //     }
        //     printf("%d %d", min(x1,x2), (max(x1,x2)));
        // }
        if (ok == 0) {
            move_figure;
        }
    }
    // printf("%c %c ", turn(x1, y1, board), turn(x2, y2, board));

    print(*board);
}
void ok(char** s, int count, char board[board_size][board_size])
{
    int j = 0;
    char figure;
    for (int i = 0; i < count; i++) {
        while (s[i][j] != '\n') {
            if (char_to_int(s[i][j]) != -1) {
                if (j == 0 && s[i][j] == 'b')
                    if (char_to_int(s[i][j + 1]) != -1)
                        j++;
                printf("%d %d %c", i, j, s[i][j]);
                if (j > 0)
                    figure = s[i][j - 1];
                else
                    figure = 'p';
                m.fmx = char_to_int(s[i][j]);
                m.fmy = 8 - (s[i][j + 1] - '0');
                m.act = s[i][j + 2];
                m.smx = char_to_int(s[i][j + 3]);
                m.smy = 8 - (s[i][j + 4] - '0');
                if (figure == (board[m.fmy][m.fmx])
                    || (figure == 'p' && tolower(board[m.fmy][m.fmx]) == 'p')) {
                    switch (tolower(figure)) {
                    case 'k':
                        move_king(info);
                        break;
                    case 'p':
                        move_pawn(info);
                        break;
                    case 'r':
                        move_rook(info);
                        break;
                    case 'n':
                        move_knight(info);
                        break;
                    case 'b':
                        move_bishop(info);
                        break;
                    }
                }
                j += 3;
            }
            j++;
        }
        printf("\n");
        j = 0;
    }
}