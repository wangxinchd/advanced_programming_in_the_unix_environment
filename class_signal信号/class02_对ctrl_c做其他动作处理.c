#include <signal.h>
#include <unistd.h>

static void int_hander(int s)
{
    write(1, "!", 1);
}



int
main()
{
    int i;

    signal(SIGINT, int_hander);

    for (i = 0; i < 10; i++)
    {
        write(1, "*", 1);
        sleep(1);
    }

    return 0;
}

/**
 
输出结果:
**^C!*^C!*^C!*^C!*^C!*^C!*^C!*^C!*^C!
这里并没有等待1s, 因为信号会打断阻塞的系统调用

 * 
*/