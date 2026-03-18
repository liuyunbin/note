
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

int main() {
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
        return 0;
    }

    sleep(1);

    return 0;
}
