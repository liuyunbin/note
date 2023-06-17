
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

int main() {
    log();
    log("测试产生僵尸进程, 不退出");
    log();
    pid_t child = fork();

    if (child == 0) {
        exit(0);
    }
    sleep(1);  // 保证子进程已启动并退出
    log("产生僵尸进程(" + std::to_string(child) + ")");
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(child);
    system(cmd.data());

    log("主进程死循环, 不退出...");
    for (;;)
        ;

    return 0;
}
