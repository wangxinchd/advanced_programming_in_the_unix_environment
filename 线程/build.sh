#! /bin/bash

rm -rf ./class01_pthread_create
rm -rf ./class02_pthread_create_join
rm -rf ./class03_cleanup
rm -rf ./class04_综合案例
rm -rf ./class04_综合案例加强版
tm -rf ./class05_竞争故障_互斥量
rm -rf ./class06_互斥量02
rm -rf ./class07_线程池筛选质数

# gcc ./class01_pthread_create.c -lpthread -o ./class01_pthread_create
# gcc ./class02_pthread_create_join.c -lpthread -o ./class02_pthread_create_join
# gcc ./class03_cleanup.c -lpthread -o ./class03_cleanup
# gcc ./class04_综合案例.c -lpthread -o ./class04_综合案例
# gcc ./class04_综合案例加强版.c -lpthread -o ./class04_综合案例加强版
# gcc ./class05_竞争故障_互斥量.c -lpthread -o ./class05_竞争故障_互斥量
# gcc ./class06_互斥量02.c -lpthread -o ./class06_互斥量02
gcc ./class07_线程池筛选质数.c -lpthread -o ./class07_线程池筛选质数