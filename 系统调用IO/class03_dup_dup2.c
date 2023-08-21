#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FNAME "/tmp/out"



// int
// main()
// {
//     int fd;

//     close(1); //
//     关闭之后再次打开，打开的是最小的可用的文件描述符，即标准输出

//     fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600); //
//     文件FNAME记录的是标准输出
//     if (fd < 0)
//     {
//         perror("open()");
//         exit(1);
//     }

//     puts("hello!");

//     exit(0);
// }

// dup 使用当前可用范围内最小的

/*
int
main()
{
    int fd;
    fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("open()");
        exit(1);
    }

// 如果这个进程没有文件描述符1，那么第一次打开就是1，现在关闭的这个操作就有问题

    close(1);  //
    dup(fd);   //
这两部操作不够原子,close之后，如果有其他线程open了，就会出现问题

    close(fd);

    puts("hello!");

    exit(0);
}
*/

int
main()
{
    int fd;
    fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("open()");
        exit(1);
    }

    dup2(fd, 1);  //如果fd 就是1的话，不需要关闭

    if (fd != 1)
    {
        close(fd);
    }

    puts("hello!");

    exit(0);
}