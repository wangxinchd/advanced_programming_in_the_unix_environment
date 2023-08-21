文件IO / 系统调用IO

fd是在文件IO中贯穿始终的类型

文件描述符的概念: （整形数，优先使用当前可用的范围内最小的）

文件io操作: open close read write lseek



将文件io和标准io的区别：
- 标准io 和 系统io不能混用 （fileno FILE转换成文件描述符 fdopen文件描述符转换成FILE）

io的效率问题：


文件共享


原子操作: 不可分割的操作
原子操作的作用：解决竞争和冲突

程序中的重定向: dup, dup2
当调用dup函数时，内核在进程中创建一个新的文件描述符，此描述符是当前可用文件描述符的最小数值，这个文件描述符指向oldfd所拥有的文件表项。
　　dup2和dup的区别就是可以用newfd参数指定新描述符的数值，如果newfd已经打开，则先将其关闭。如果newfd等于oldfd，则dup2返回newfd, 而不关闭它。dup2函数返回的新文件描述符同样与参数oldfd共享同一文件表项。

　　实际上，调用dup(oldfd)等效于，fcntl(oldfd, F_DUPFD, 0)
　　而调用dup2(oldfd, newfd)等效于，close(oldfd)；fcntl(oldfd, F_DUPFD, newfd)；


同步: sync, fsync, fdatasync


fcntl(); // 文件描述符
ioctl(); //设备相关一定会用到


/dev/fd/目录: 