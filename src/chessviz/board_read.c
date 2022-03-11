#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void board_read(int argc, char **argv)
{
    int count=0;
    char** s=(char**)malloc(sizeof(char*));
    int size=0;
    if(argc==1)
    {
        printf("Введите количество ходов: ");
        scanf("%d", &count);
    }
    else
    {
        FILE* fp=fopen(argv[1], "r");
        while(!feof(fp))
        {
            s[size]=(char*)malloc(sizeof(char)*256);
            fscanf(fp, "%s", s[size]);
            size++;
            s = (char**)realloc(s, sizeof(char*)*(size + 1));
        }
    }
    for(int n=0;n<size;n++)
    {
        printf("%s\n", s[n]);
    }
    free(s);
}