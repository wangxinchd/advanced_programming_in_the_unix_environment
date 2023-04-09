#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define LEFT      30000000
#define RIGHT     30000200
#define THENUM    (RIGHT - LEFT + 1)

typedef struct thr_arg_st
{
    int n;
} thr_arg_st_t;

static void *
thr_prime(void *p)
{
    int i, j, mark;
    i = ((thr_arg_st_t*) p)->n;
    // free(p);

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
        printf("%d is a primer\n", i);
    }

    pthread_exit(p); // 退出进程之后将需要free的地址传递出去
}

int
main()
{
    int i, err;
    pthread_t tid[THENUM];
    thr_arg_st_t *p;
    void *ptr;

    for (i = LEFT; i <= RIGHT; i++)
    {
        p = malloc(sizeof(*p));
        if (p == NULL)
        {
            perror("malloc()");
            exit(1);
        }
        p->n = i;

        err = pthread_create(tid + i - LEFT, NULL, thr_prime, p);
        if (err)
        {
            fprintf(stderr, "pthread_create(): %s\n", strerror(err));
            exit(1);
        }
    }

    for (i = LEFT; i < RIGHT; i++)
    {
        pthread_join(tid[i-LEFT], &ptr);
        free(ptr); // 收尸得到需要free的进程
    }

    exit(0);
    return 0;
}
