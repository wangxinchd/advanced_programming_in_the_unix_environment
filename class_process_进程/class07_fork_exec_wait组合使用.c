#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int
main()
{
    pid_t pid;
    puts("Begin!");

    pid = fork();
    if (pid < 0)
    {
        perror("fork() ");
        exit(1);
    }

    if (pid == 0)
    {
        execl("/bin/date", "date", "+%s", NULL);
        perror("execl failed ");
        exit(1);
    }

    wait(NULL);

    puts("End!");

    return 0;
}

/*
父子进程使用同样的文件描述符（在创建子进程的瞬间，子进程继承了所有的父进程的文件描述符）

如果直接执行:
Begin!
1681630032
End!


如果重定向到文件:
可能的输出
1681630036
Begin!
End!


*/