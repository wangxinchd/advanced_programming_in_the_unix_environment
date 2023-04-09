
# 线程

## 1. 线程的概念
一个正在运行的函数。posix线程是一套标准，而不是实现，其他实现方式，例如openmp线程。posix线程标识：pthread_t

## 2. 线程常用函数
### 判断线程是否相同
- pthread_equal用于比较两个线程是否相同
### 返回当前线程标识
- pthread_self
### 线程创建
- pthread_create 例子class01_pthread_create.c
- pthread_create();
- 线程的调度取决于调度器的策略


### 线程取消
- pthread_cancel() 一般先取消然后pthread_join()
- 线程取消的选项
  - 取消的两种状态：允许和不允许
  - 允许取消又分为：异步cancel，推迟cancel(默认，推迟至cancel点响应)
  - cancel点： POSIX定义的cancel点，都是可能引发阻塞的系统调用
  - pthread_setcancelstate()设置是否允许取消
  - pthread_setcanceltype() 设置取消方法
  - pthread_testcancel() 本函数什么都不做，就是一个取消点
### 线程分离
- pthread_detach()参数就是进程pthread_t

### 线程的终止方式
- 1.线程从启动例程返回，返回值就是线程的退回码
- 2.线程可以被同一进程中的其他线程取消
- 线程调用pthread_exit()函数退出

### 线程的收尸
pthread_join() -> 等待线程结束，例子 class02_pthread_create_join.c

### 栈区的清理
- pthread_cleanup_push() 挂钩子函数
- pthread_cleanup_pop() 取钩子函数



## 3. 线程的同步
- 互斥量 pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy
- 

## 4. 线程的属性
线程同步的属性

## 5. 重入