#include <stdio.h>
#include <unistd.h>


extern char **environ;


int main()
{
    puts("Begin!");
    // fflush(NULL);
    execl("/bin/date", "date", "+%s", NULL);  // exec 函数将该进程的内核映像进行修改了
    perror("exec() ");
    puts("End!");  // 不会输出

    return 0;
}

/**
输出的内容如下:
Begin!
1681629068


如果输出重定向  ./可执行文件 > log.log
1681629068
这种情况没有Begin!


int main()
{
    puts("Begin!");
    fflush(NULL);
    execl("/bin/date", "date", "+%s", NULL);  // 采用了新的进程映像代替了原有的映像，缓存区被清除了
    perror("exec() ");
    puts("End!");  // 不会输出

    return 0;
}
有了fflush将输出下面的内容
Begin!
1681629068

*/