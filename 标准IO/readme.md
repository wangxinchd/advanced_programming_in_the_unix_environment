test01_fopen.c
1. 提供了errno 这个错误的两种输出
2. 标准错误 stderr
3. fprintf的使用

test02_fclose.c
1. 测试fclose函数

test03_max_fopen_num.c
1. ulimit -a使用
2. 能够打开的最多文件个数是1024
3. 创建文件的权限是664. 创建文件的权限来自于 0666 & ~umask  (umask默认是0002)

test04_mycopy.c
1. fgetc 和 fputc函数的使用
2. 实现文件的copy

test05_count_file_size.c
1. 实现了统计文件的大小

test06_mycopy_fgets_fputs.c
1. fgets 和 fputs函数的使用
2. 实现的文件的copy