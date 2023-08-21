#include <stdio.h>
#include <unistd.h>



int
main()
{
    pid_t pid;

    printf("[%d] Begin() \n", getpid());  // parent

    // fflush(NULL);
    pid = fork();

    if (pid < 0)
    {
        perror("fork() ");
    }

    if (pid == 0)  // child
    {
        printf("[%d]: Child is working \n", getpid());
    }
    else  //parent
    {
        printf("[%d]: Parent is working \n", getpid());
    }

    printf("[%d] End!\n", getpid());

    // getchar();
    exit(0);
}


/*

如果    printf("[%d] Begin() ", getpid());  // parent
输出：
[28261] Begin() [28261]: Parent is working 
[28261] End!
[28261] Begin() [28262]: Child is working 
[28262] End!

[28261] Begin()被输出了两次，因为存在缓冲区

如果
printf("[%d] Begin() \n", getpid());  // parent
[28767] Begin() 
[28767]: Parent is working 
[28767] End!
[28768]: Child is working 
[28768] End!

[28261] Begin()被输出了1次，因为在创建进程之前已经刷新了缓冲区

但是
如果采用 ./可执行文件 > log.log , 
[30765] Begin() 
[30765]: Parent is working 
[30765] End!
[30765] Begin() 
[30766]: Child is working 
[30766] End!

[30765] Begin() 还是会输出两遍，因为采用了重定向，文件的话是全缓冲的模式

*/