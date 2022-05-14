#include <libchessviz/move.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
char** board_read(int argc, char** argv, int count)
{
    int size = 0;
    // int j = 0;
    char** s = (char**)malloc(sizeof(char*));
    if (argc == 1) { // read from stdin
        printf("%d. ", count);
        s[size]=(char*)malloc(sizeof(char) * 256);
        fgets(s[size],256,stdin);
    } else { // read from file
        FILE* fp = fopen(argv[1], "r");
        while (!feof(fp)) {
            s[size] = (char*)malloc(sizeof(char) * 256);
            fgets(s[size], 256, fp);
            size++;
            s = (char**)realloc(s, sizeof(char*) * (size + 1));
        }
        --size;
        fclose(fp);
    }
    return s;
}