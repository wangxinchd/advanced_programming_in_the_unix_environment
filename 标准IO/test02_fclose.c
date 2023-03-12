#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *fp; // 指针指向的空间是在堆区

    fp = fopen("tmp", "w");
    if (fp == NULL)
    {
        // errno是一个宏定义
        perror("fopen() failed");

        // 采用fprintf向标准错误输出
        fprintf(stderr, "fopen() failed: %s\n", strerror(errno));
    }

    fclose(fp); // 失败返回EOF, 成功返回0, 一般都是的成功,所以不会去做校验

    return 0;
}
