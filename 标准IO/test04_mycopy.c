#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int ch;// 因为有-1失败的情况，所以定义int类型代替 char类型
    FILE *fps, *fpd;
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <src_file> <dist_file>\n", argv[0]);
        exit(1);
    }

    fps = fopen(argv[1], "r");
    if (fps == NULL)
    {
        perror("fopen() failed");
        exit(1);
    }

    fpd = fopen(argv[2], "w");
    if (fpd == NULL)
    {
        fclose(fps);
        perror("fopen() failed");
        exit(1);
    }

    while(1)
    {
        ch = fgetc(fps); // 返回值是一个int类型
        if (ch == EOF)
        {
            break;
        }
        fputc(ch, fpd); // int fputc(int c, FILE *stream);
    }

    fclose(fpd); // 先关闭需要依赖别人的文件指针
    fclose(fps);

    return 0;
}