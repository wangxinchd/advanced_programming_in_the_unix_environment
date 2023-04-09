#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THD_NUM (4)



/*创建4个线程，4个线程依次只能输出a,b,c,d, 实现在终端顺序输出 abcd abcd*/
static pthread_mutex_t mut[THD_NUM] = PTHREAD_MUTEX_INITIALIZER;

static void *
thd_func(void *p)
{
    int n = (int) p;
    int c = 'a' + n;
    while (1)
    {
        pthread_mutex_lock(mut + n);  // 对当前线程加锁
        write(1, &c, 1);
        pthread_mutex_unlock(mut + (n + 1) % 4); // 对下一个线程解锁
    }
    pthread_exit(NULL);
}

int main()
{
    int i, err;
    pthread_t tid[THD_NUM];

    for (i = 0; i < THD_NUM; i++)
    {
        pthread_mutex_init(mut + i, NULL);
        pthread_mutex_lock(mut + i); // 即使线程被创建也不做任何操作
        pthread_create(tid+i, NULL, thd_func, (void *) i);
    }
    pthread_mutex_unlock(mut);

    alarm(1);

    for (i = 0; i < THD_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }

    return 0;
}