
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

// 测试跨函数跳转
jmp_buf buf_jmp;

void test_jmp(int v) {
    if (v == 0) {
        longjmp(buf_jmp, 3);
    }

    if (v == 3) {
        if (setjmp(buf_jmp) == 0) {
            log("第一次经过, v = " + std::to_string(v));
        } else {
            log("再一次经过, v = " + std::to_string(v));
            return;
        }
    }
    log("参数: v = " + std::to_string(v));
    test_jmp(v - 1);
}

int main() {
    log("测试 jmp");
    test_jmp(10);

    return 0;
}
