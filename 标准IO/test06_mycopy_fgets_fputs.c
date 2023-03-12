#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int
main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE] = {0};
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

    while(fgets(buffer, BUFFER_SIZE, fps) != NULL)
    {
        fputs(buffer, fpd); // int fputc(int c, FILE *stream);
    }

    fclose(fpd); // 先关闭需要依赖别人的文件指针
    fclose(fps);

    return 0;
}