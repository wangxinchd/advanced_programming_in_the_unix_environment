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

    puts("End!");
    exit(0); // 在程序的某个位置，直接让进程结束
}

// gcc class01_pthread_create.c -lpthread