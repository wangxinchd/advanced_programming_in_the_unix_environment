#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define THR_NUM (20)
#define FILENAME "/tmp/out"
#define BUFFERSIZE (1024)



/*
题目要求：创建20个进程，每个进程都需要打开/tmp/out文件，读取里面的数字，并+1覆盖保存

    执行可执行文件前需要先 echo 1 > /tmp/out 即在/tmp/下创建out文件，文件只有一个数字1
    下面关于mut的操作是添加互斥量，如果没有这个，会产生冲突（每次输出的结果都不会一致）
*/

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // 创建互斥量

void *
thr_add(void *p)
{
    FILE *fp;
    char buffer[BUFFERSIZE];
    int value;

    fp = fopen(FILENAME, "r+");
    if (fp == NULL)
    {
        perror("fopen failed");
        exit(1);
    }

    pthread_mutex_lock(&mut); // 加锁

    fgets(buffer, BUFFERSIZE, fp);
    value = atoi(buffer);
    value++;
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", value);
    fclose(fp);

    pthread_mutex_unlock(&mut); // 开锁
    pthread_exit(NULL);
}

int
main()
{
    int i, err;

    pthread_t tid[THR_NUM];

    for (i = 0; i < THR_NUM; i++)
    {
        err = pthread_create(tid + i, NULL, thr_add, NULL);
        if (err)
        {
            fprintf(stderr, "pthread_create failed %s", strerror(err));
            exit(1);
        }
    }

    for (i = 0; i < THR_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mut); // 销毁互斥量

    return 0;

}