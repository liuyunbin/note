
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
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

int main() {
    // 测试宏
    test_macro();

    // 测试可变参数
    test_va();

    return 0;
}
