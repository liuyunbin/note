
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

// 日志输出
template <typename T>
std::string to_string(T data) {
    std::stringstream tmp;
    tmp << data;
    return tmp.str();
}

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

// 测试资源限制

/*
 * ulimit -c -------- 查看 core 文件大小的软限制
 * ulimit -d -------- 限制程序数据段的大小
 * ulimit -e -------- 限制程序优先级
 * ulimit -f -------- 限制文件大小
 * ulimit -i -------- 限制待决的信号的数量
 * ulimit -l -------- 限制加锁的内存大小
 * ulimit -m -------- 限制物理内存大小
 * ulimit -n -------- 限制打开文件的最大个数
 * ulimit -p -------- 限制匿名管道的缓冲大小 -- 可能没有设置
 * ulimit -q -------- 限制消息队列的大小
 * ulimit -r -------- 限制任务调度优先级
 * ulimit -R -------- 限制任务调度时, CPU 大最大使用时间
 * ulimit -s -------- 限制栈大小
 * ulimit -t -------- 限制 CPU 总的使用时间
 * ulimit -u -------- 限制进程数
 * ulimit -v -------- 限制虚拟内存大小
 * ulimit -x -------- 限制文件锁的个数
 */

#define TEST_LIMIT(name, X)                                  \
    {                                                        \
        struct rlimit rlim;                                  \
        getrlimit(X, &rlim);                                 \
        log(name + std::string(": ") + #X);                  \
        if (rlim.rlim_cur == RLIM_INFINITY)                  \
            log("软限制: " + std::string("不限制"));         \
        else                                                 \
            log("软限制: " + std::to_string(rlim.rlim_cur)); \
        if (rlim.rlim_max == RLIM_INFINITY)                  \
            log("硬限制: " + std::string("不限制"));         \
        else                                                 \
            log("硬限制: " + std::to_string(rlim.rlim_max)); \
        log();                                               \
    }

int main() {
    log();
    log("测试资源限制: ");
    log();
    TEST_LIMIT("虚拟内存大小", RLIMIT_AS);
    TEST_LIMIT("core 文件大小", RLIMIT_CORE);
    TEST_LIMIT("CPU 总的时间大小", RLIMIT_CPU);
    TEST_LIMIT("数据段(初始化数据, 未初始化数据, 堆)", RLIMIT_DATA);
    TEST_LIMIT("文件大小", RLIMIT_FSIZE);
    TEST_LIMIT("文件锁的个数", RLIMIT_LOCKS);
    TEST_LIMIT("内存中可以锁定的大小", RLIMIT_MEMLOCK);
    TEST_LIMIT("消息队列的大小", RLIMIT_MSGQUEUE);
    TEST_LIMIT("进程优先级的上限", RLIMIT_NICE);
    TEST_LIMIT("文件描述符的最大限制", RLIMIT_NOFILE);
    TEST_LIMIT("用户的进程线程数", RLIMIT_NPROC);
    TEST_LIMIT("物理内存大小", RLIMIT_RSS);
    TEST_LIMIT("调度的优先级", RLIMIT_RTPRIO);
    TEST_LIMIT("调度时 CPU 的最大耗时 毫秒", RLIMIT_RTTIME);
    TEST_LIMIT("信号队列的长度", RLIMIT_SIGPENDING);
    TEST_LIMIT("栈大小", RLIMIT_STACK);

    return 0;
}
