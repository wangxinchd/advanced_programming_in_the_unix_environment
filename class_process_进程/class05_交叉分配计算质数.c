
#include <stdio.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200

#define PTH_NUM 3

#define IS_CARE_PROCESS_STATE 1

int
main()
{
    int i, j, k, mark;
    pid_t pid;
    for (i = 0; i < PTH_NUM; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork: "); // 不能解决，如果前两个进程创建成功，第三个进程创建失败的bug
            exit(1);
        }

        if (pid == 0) // child
        {
            for (j = LEFT + i; j <= RIGHT; j += PTH_NUM)
            {
                mark = 1;
                for (k = 2; k < j / 2; k++)
                {
                    if (j % k == 0)
                    {
                        mark = 0;
                        break;
                    }
                }

                if (mark)
                {
                    printf("[%d]: %d is a prime.\n", i, j);
                }
            }
            exit(0);
        }
    }

#if IS_CARE_PROCESS_STATE
    for (i = 0; i <= PTH_NUM; i++)
    {
        wait(NULL);
    }
#elif
    int state;
    for (i = LEFT; i <= RIGHT; i++)
    {
        wait(&state);
    }

#endif

    return 0;
}
