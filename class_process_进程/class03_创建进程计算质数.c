#include <stdio.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200

#define PTH_NUM (LEFT - RIGHT)

int
main()
{
    int i, j, mark;
    pid_t pid;
    for (i = LEFT; i <= RIGHT; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork: ");
            exit(1);
        }

        if (pid == 0) // child
        {
            mark = 1;
            for (j = 2; j < i / 2; j++)
            {
                if (i % j == 0)
                {
                    mark = 0;
                    break;
                }
            }

            if (mark)
            {
                printf("%d is a prime.\n", i);
            }
            exit(0);
        }
    }

    return 0;
}
