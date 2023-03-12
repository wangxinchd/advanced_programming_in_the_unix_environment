#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *fp; // 指针指向的空间是在堆区

    fp = fopen("tmp", "r");
    if (fp == NULL)
    {
        // errno是一个宏定义
        perror("fopen() failed");

        // 采用fprintf向标准错误输出
        fprintf(stderr, "fopen() failed: %s\n", strerror(errno));
    }

    return 0;
}
