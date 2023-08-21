# 信号并发

## 信号
### 信号的概念
  1. 信号是软件层面的中端
  2. 信号的响应依赖于中断
  3. kill -l 查看所有的信号
同步: 
异步: 异步事件的处理
- 查询法 (发生频率比较高)
- 通知法 (发生频率比较低)

### 信号定义
- signal()
- typedef void (*sighandler_t)(int);
- sighandler_t signal(int signum, sighandler_t handler);
- 备注: SIGINT ctrl + c, SIGKILL 9, SIGTERM: killall


### 信号的不可靠
- 信号的行为不可靠


### 可重入函数
- 第一次调用还没有结束，就发生第二次调用，第一次不会出错
- 所有的系统调用都是可重入的，比如open read，一部分库函数也是可重入的，比如说 memcpy,

### 信号的响应过程
- 信号从收到到响应应有一个不可避免的延迟
- 思考: 
  - 如何忽略掉一个信号?
  - 标准信号为什么要丢失
  - 标准信号的响应没有严格的顺序

- 相关的常用函数
  - kill 发送信号
  - raise 给自己发信号
  - alarm
  - pause 等待
  - abort()
  - system()
  - sleep()

- 信号集
- 信号屏蔽字/pending集的处理
- 扩展
  - sigsuspend
  - sigaction
  - setitimer()