
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

/********************************
 *
 *         公共函数
 *
 ********************************/
// 日志输出
template <typename T>
std::string to_string(T data) {
    std::stringstream tmp;
    tmp << data;
    return tmp.str();
}

template <typename T, typename... Args>
std::string to_string(T data, Args... args) {
    std::stringstream tmp;
    tmp << data;
    return tmp.str() + to_string(args...);
}

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

template <typename... Args>
void log(Args... args) {
    log(to_string(args...));
}

/****************************************
 *
 *              测试进程
 *
 ****************************************/

void test_env() {
    log("环境变量 PATH: ", getenv("PATH"));
    log("修改环境变量");
    char str[] = "PATH=LYB";
    putenv(str);
    log("环境变量 PATH: ", getenv("PATH"));
}

// 测试跨函数跳转
jmp_buf buf_jmp;

void test_jmp(int v) {
    if (v == 0) {
        longjmp(buf_jmp, 3);
    }

    if (v == 3) {
        if (setjmp(buf_jmp) == 0) {
            log("第一次经过, v = ", v);
        } else {
            log("再一次经过, v = ", v);
            return;
        }
    }
    log("参数: v = ", v);
    test_jmp(v - 1);
}

void test_jmp() {
    log("测试 jmp");
    test_jmp(10);
}

// 测试退出
class A {
  public:
    A() {
        log("调用构造函数");
    }

    ~A() {
        log("调用析构函数");
    }
};

void test_1() {
    log("测试函数-1");
}

void test_2() {
    log("测试函数-2");
}

void test_atexit() {
    log("注册退出函数");
    atexit(test_1);
    atexit(test_1);
    atexit(test_2);
    atexit(test_2);
}

void test_exit() {
    if (fork() == 0) {
        log("测试 exit");
        A a;
        test_atexit();
        log("退出");
        exit(0);
    }

    sleep(1);
    log();

    if (fork() == 0) {
        log("测试 _exit");
        A a;
        test_atexit();
        log("退出");
        _exit(0);
    }

    sleep(1);
    log();

    if (fork() == 0) {
        log("测试正常退出");
        A a;
        test_atexit();
        log("退出");
        return;
    }

    sleep(1);
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

#define TEST_LIMIT(name, X)                 \
    {                                       \
        struct rlimit rlim;                 \
        getrlimit(X, &rlim);                \
        log(name, ": ", #X);                \
        if (rlim.rlim_cur == RLIM_INFINITY) \
            log("软限制: ", "不限制");      \
        else                                \
            log("软限制: ", rlim.rlim_cur); \
        if (rlim.rlim_max == RLIM_INFINITY) \
            log("硬限制: ", "不限制");      \
        else                                \
            log("硬限制: ", rlim.rlim_max); \
        log();                              \
    }

void test_limit() {
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
}

// 测试 vfork
void test_vfork_help() {
    std::string str = "123";
    log("调用 vfork 前为: ", str);
    if (vfork() == 0) {
        str = "456";
        log("vfork 内修改为: ", str);
        exit(0);
    }
    log("调用 vfork 后为: ", str);
}

void test_vfork() {
    std::string str = "123";
    log("上一层函数调用前为: ", str);
    test_vfork_help();
    log("上一层函数调用后为: ", str);
}

void test_process() {
    // 测试环境变量
    // test_env();

    // 测试跨函数跳转
    // test_jmp();

    // 测试退出
    // test_exit();

    // 测试资源限制
    // test_limit();

    // 测试 vfork
    // test_vfork();
}

/****************************************
 *
 *              测试 C++
 *
 ****************************************/

// 测试宏
int v123 = 123456;

#define TEST_MACRO_STR(fmt, X) printf(fmt, #X, X)
#define TEST_MACRO_CAT(fmt, X) printf(fmt, v##X)
// 可变参数, 如果可变参数不存在, 去掉前面的逗号
#define TEST_MACRO(fmt, ...) printf(fmt, ##__VA_ARGS__)

void test_macro() {
    TEST_MACRO_STR("测试宏变字符串: %s -> %d\n", 123);
    TEST_MACRO_CAT("测试    宏连接: %d\n", 123);
    TEST_MACRO("测试宏有可变参数: %d\n", 123);
    TEST_MACRO("测试宏无可变参数\n");
}

// 测试可变参数
//    printf() -- 输出到标准输出
//   fprintf() -- 输出到标准IO
//   dprintf() -- 输出到文件描述符
//   sprintf() -- 输出到字符串
//  snprintf() -- 输出到字符串
//
//   vprintf() -- 使用可变参数 va
//  vfprintf() -- 使用可变参数 va
//  vdprintf() -- 使用可变参数 va
//  vsprintf() -- 使用可变参数 va
// vsnprintf() -- 使用可变参数 va
//
//  __VA_ARGS__  -- 只能在宏中使用, 代替可变参数
//
//  va_start -- 初始化
//  va_arg   -- 获取下一个可变参数
//  va_copy  -- 拷贝
//  va_end   -- 清空

#define TEST_VA(fmt, ...) printf(fmt, ##__VA_ARGS__)

void test_va_c(const char* s, ...) {
    va_list ap;
    va_start(ap, s);
    vprintf(s, ap);
    va_end(ap);
}

void test_va_cpp() {
}

template <typename T, typename... Args>
void test_va_cpp(T t, Args... args) {
    std::cout << t;
    test_va_cpp(args...);
}

void test_va() {
    TEST_VA("测试 C   风格的可变参数: %s -> %s\n", "123", "456");
    test_va_c("测试 C   风格的可变参数: %s -> %s\n", "123", "456");
    test_va_cpp("测试 C++ 风格的可变参数: ", "123", " -> ", "456", "\n");
}

void test_cpp() {
    // 测试宏
    // test_macro();

    // 测试可变参数
    // test_va();
}

int main() {
    test_process();  // 测试进程
    test_cpp();      // 测试 cpp

    return 0;
}
