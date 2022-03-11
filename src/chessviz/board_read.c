#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
void board_read(int argc, char **argv)
{
    int count=0, size=0;
    char** s=(char**)malloc(sizeof(char*));
    if(argc==1)
    {
        printf("Введите количество ходов: ");
        scanf("%d", &count);
        for(int i=0;i<=count;i++)
        {
            s[size]=(char*)malloc(sizeof(char)*256);
            fgets(s[size], 10, stdin);
        // printf("ladno= %s\n", s[0]);

            size++;
            s = (char**)realloc(s, sizeof(char*)*(size + 1));
        }
        for(int n=0;n<size-1;n++)
        {
            s[n]=s[n+1];
        }
        --size;
        s[size]=NULL;
        //free(str);
    }
    else
    {
        FILE* fp=fopen(argv[1], "r");
        while(!feof(fp))
        {
            s[size]=(char*)malloc(sizeof(char)*256);
            fgets(s[size], 256, fp);
            size++;
            s = (char**)realloc(s, sizeof(char*)*(size + 1));
        }
    }
    for(int n=0;n<size;n++)
    {
        printf("%d = %s\n", n, s[n]);
    }
    free(s);
}