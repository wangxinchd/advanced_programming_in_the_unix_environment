#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *func(void *p)
{
    puts("Tread is working!");
    return NULL;
}

int main()
{
    int err;
    pthread_t tid;
    puts("begin!");

    err = pthread_create(&tid, NULL, func, NULL);

    if (err)
    {
        fprintf(stderr, "pthread_create failed %s \n", strerror(err));
        exit(1);
    }

    pthread_join(tid, NULL); // 等待线程结束
    puts("End!");
    exit(0); // 在程序的某个位置，直接让进程结束
}

// gcc class02_pthread_create_join.c -lpthread

/*
终端输出结果
begin!
Tread is working!
End!

*/

