
#include "lshell.h"

#define LIMIT(name, X)                                                       \
    {                                                                        \
        struct rlimit rlim;                                                  \
        getrlimit(X, &rlim);                                                 \
        std::string s_cur;                                                   \
        if (rlim.rlim_cur == RLIM_INFINITY)                                  \
            s_cur = "unlimited";                                             \
        else                                                                 \
            s_cur = std::to_string(rlim.rlim_cur);                           \
        std::string s_max;                                                   \
        if (rlim.rlim_max == RLIM_INFINITY)                                  \
            s_max = "unlimited";                                             \
        else                                                                 \
            s_max = std::to_string(rlim.rlim_max);                           \
        printf("%20s %10s %10s %s\n", #X, s_cur.data(), s_max.data(), name); \
    }

int do_ulimit(int argc, char* argv[]) {
    LIMIT("虚拟内存大小", RLIMIT_AS);
    LIMIT("core 文件大小", RLIMIT_CORE);
    LIMIT("CPU 总的时间大小", RLIMIT_CPU);
    LIMIT("数据段(初始化数据, 未初始化数据, 堆)", RLIMIT_DATA);
    LIMIT("文件大小", RLIMIT_FSIZE);
    LIMIT("文件锁的个数", RLIMIT_LOCKS);
    LIMIT("内存中可以锁定的大小", RLIMIT_MEMLOCK);
    LIMIT("消息队列的大小", RLIMIT_MSGQUEUE);
    LIMIT("进程优先级的上限", RLIMIT_NICE);
    LIMIT("文件描述符的最大限制", RLIMIT_NOFILE);
    LIMIT("用户的进程线程数", RLIMIT_NPROC);
    LIMIT("物理内存大小", RLIMIT_RSS);
    LIMIT("调度的优先级", RLIMIT_RTPRIO);
    LIMIT("调度时 CPU 的最大耗时 毫秒", RLIMIT_RTTIME);
    LIMIT("信号队列的长度", RLIMIT_SIGPENDING);
    LIMIT("栈大小", RLIMIT_STACK);
    return 0;
}
