#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int count=0;// 因为有-1失败的情况，所以定义int类型代替 char类型
    FILE *fp;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file> \n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    while(fgetc(fp) != EOF)
    {
        count++;
    }
    printf("count = %d\n", count); //认为文件的大小没有超过int最大值
    fclose(fp);
    return 0;
}