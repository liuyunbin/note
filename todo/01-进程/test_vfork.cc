
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

// 测试 vfork
void test_vfork_help() {
    std::string str = "123";
    log("调用 vfork 前为: " + str);
    if (vfork() == 0) {
        str = "456";
        log("vfork 内修改为: " + str);
        exit(0);
    }
    log("调用 vfork 后为: " + str);
}

int main() {
    std::string str = "123";
    log("上一层函数调用前为: " + str);
    test_vfork_help();
    log("上一层函数调用后为: " + str);

    return 0;
}
