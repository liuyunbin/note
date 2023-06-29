
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>

void test_va();     // 测试可变参数
void test_macro();  // 测试宏
void test_exit();   // 测试退出
void test_jmp();    // 测试跨函数跳转
void test_limit();  // 测试资源限制

int main() {
#if 0
    test_macro();  // 测试宏
#endif

#if 0
    test_va();  // 测试可变参数
#endif

#if 0
    test_exit();  // 测试退出
#endif

#if 0
    test_jmp(); // 测试跨函数跳转
#endif

    //    std::cout << "环境变量 PATH: " << getenv("PATH") << std::endl;

#if 1
    test_limit();  // 测试资源限制
#endif

    return 0;
}

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
//

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
    TEST_VA("测试 C 风格的可变参数: %s -> %s\n", "123", "456");
    test_va_c("测试 C 风格的可变参数: %s -> %s\n", "123", "456");
    test_va_cpp("测试 C++ 风格的可变参数: ", "123", " -> ", "456", "\n");
}

// 测试退出
class A {
  public:
    A() {
        std::cout << "调用构造函数" << std::endl;
    }

    ~A() {
        std::cout << "调用析构函数" << std::endl;
    }
};

void test_1() {
    std::cout << "测试函数-1" << std::endl;
}

void test_2() {
    std::cout << "测试函数-2" << std::endl;
}

void test_atexit() {
    std::cout << "注册退出函数" << std::endl;
    atexit(test_1);
    atexit(test_1);
    atexit(test_2);
    atexit(test_2);
}

void test_exit() {
    if (fork() == 0) {
        std::cout << "测试 exit" << std::endl;
        A a;
        test_atexit();
        std::cout << "退出" << std::endl;
        exit(0);
    }

    sleep(1);
    std::cout << std::endl;

    if (fork() == 0) {
        std::cout << "测试 _exit" << std::endl;
        A a;
        test_atexit();
        std::cout << "退出" << std::endl;
        _exit(0);
    }

    sleep(1);
    std::cout << std::endl;

    if (fork() == 0) {
        std::cout << "测试正常退出" << std::endl;
        A a;
        test_atexit();
        std::cout << "退出" << std::endl;
        return;
    }

    sleep(1);
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

// 测试资源限制
// 软限制值可以任意修改, 只要小于等于硬限制值即可
// 硬限制值可以降低, 只要大于等于软限制值即可
// 只有超级用户才可以提高硬限制值
// RLIM_INFINITY 表示不做限制

#define TEST_LIMIT(X)                   \
    {                                   \
        struct rlimit rlim;             \
        getrlimit(X, &rlim);            \
        log(#X);                        \
        log("软限制: ", rlim.rlim_cur); \
        log("硬限制: ", rlim.rlim_max); \
        log();                          \
    }

void test_limit() {
    log("测试资源限制: ");
    log();
    TEST_LIMIT(RLIMIT_CPU);
    TEST_LIMIT(RLIMIT_CORE);
}
