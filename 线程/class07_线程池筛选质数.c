#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define LEFT      30000000
#define RIGHT     30000200
#define THRNUM    4 //创建制定的4个线程

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;


/**
 * num = 0 无任务
 * num > 0 任务
 * num = -1 任务结束
*/


/*
 * main线程用于产生任务，为其他线程收尸
 * 其他线程用于计算是否为质数
*/

static void *
thr_prime(void *p)
{
    int i, j, mark;

    while (1)
    {
        pthread_mutex_lock(&mut_num); // 首先加锁

        while (num == 0) // 看看是否等于0，如果等于0，说明此时无任务，需要解锁，让main线程产生任务
        {
            pthread_mutex_unlock(&mut_num);
            sched_yield();
            pthread_mutex_lock(&mut_num);
        }

        if (num == -1)
        {
            pthread_mutex_unlock(&mut_num);
            break;
        }

        i = num; // 将 需要计算质数的值，传递给计算的线程，然后将num置为0，交给main线程去产生任务
        num = 0;

        pthread_mutex_unlock(&mut_num);
        mark = 1;

        for (j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                mark = 0;
                break;
            }
        }

        if (mark)
        {
            printf("[%d]: %d is a primer\n", (int)p, i);
        }
    }

    pthread_exit(NULL); // 退出进程之后将需要free的地址传递出去
}

int
main()
{
    int i, err;
    pthread_t tid[THRNUM];

    for (i = 0; i < THRNUM; i++)
    {
        err = pthread_create(tid + i, NULL, thr_prime, (void *)i);
        if (err)
        {
            fprintf(stderr, "pthread_create(): %s\n", strerror(err));
            exit(1);
        }
    }

    /* 创建任务 */
    for (i = LEFT; i <= RIGHT; i++)
    {
        pthread_mutex_lock(&mut_num);

        while (num != 0)
        {
            // if num != 0 说明任务没有被抢走，所以解锁，让别人去强任务
            pthread_mutex_unlock(&mut_num);
            // sleep(1);
            sched_yield();  // 出让调度器，希望别的线程拿到num的值  稍微停一下
            pthread_mutex_lock(&mut_num);
        }

        num = i;
        pthread_mutex_unlock(&mut_num);
    }

    pthread_mutex_lock(&mut_num);
    while (num != 0)
    {
        pthread_mutex_unlock(&mut_num);
        sched_yield(); // 出让调度器，希望别的线程拿到num的值  稍微停一下

        pthread_mutex_lock(&mut_num);
    }

    num = -1;
    pthread_mutex_unlock(&mut_num);

    for (i = 0; i < THRNUM; i++)
    {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mut_num);
    return 0;
}
