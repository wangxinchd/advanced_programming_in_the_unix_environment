#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *fp; // 指针指向的空间是在堆区
    int i;

    i = 0;
    while(1)
    {
        fp = fopen("tmp", "r");

        if (fp == NULL)
        {
            // errno是一个宏定义
            printf("open file num is %d\n", i);
            perror("fopen() failed");
            break;
        }
        i++;
    }

    return 0;
}

// 输出的信息，剩下的3个文件是标准输入 标准输出 标准错误
// open file num is 1021
// fopen() failed: Too many open files

/*
uisee@uisee-ThinkPad-T470:~/uos/BaseTools/advanced_programming_in_the_unix_environment/标准IO[master]$ ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 63247
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024  打开文件的总个数
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 63247
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
*/