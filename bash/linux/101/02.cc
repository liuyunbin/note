
#ifndef LOG_H_
#define LOG_H_

#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
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

std::string get_time() {
    time_t now = time(NULL);
    struct tm* info = localtime(&now);
    char buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    return buf;
}

void log(const std::string& msg = "") {
    std::cout << get_time() << " " << msg << std::endl;
}

#endif

void test(const std::string& str, int x, int y) {
    std::cout << std::endl;
    std::cout << "测试: " << str << std::endl;
    std::cout << "求商: " << x / y << std::endl;
    std::cout << "求余: " << x % y << std::endl;
}

int main() {
    int x = std::numeric_limits<int>::max();
    std::cout << "测试有符号整数max      :" << x << std::endl;
    x = x + 10;
    std::cout << "测试有符号整数max + 10 :" << x << std::endl;

    unsigned y = std::numeric_limits<unsigned int>::max();
    std::cout << "测试无符号整数max      :" << y << std::endl;
    y = y + 10;
    std::cout << "测试无符号整数max + 10 :" << y << std::endl;

    test("5/2", 5, 2);
    test("5/-2", 5, -2);
    test("-5/2", -5, 2);
    test("-5/-2", -5, -2);

    return 0;
}
