#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void
cleanup_func(void *p)
{
    puts(p);
}

void *
func(void *p)
{
    puts("Tread is working!");

    pthread_cleanup_push(cleanup_func, "cleanup:1");
    pthread_cleanup_push(cleanup_func, "cleanup:2");
    pthread_cleanup_push(cleanup_func, "cleanup:3");

    puts("push over!");

    pthread_cleanup_pop(1); // 1执行钩子函数，0不执行
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(1);
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

// gcc class03_cleanup.c -lpthread

/*
终端输出结果
begin!
Tread is working!
End!

*/

