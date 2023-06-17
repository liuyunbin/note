
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

void show(pid_t pid) {
    std::string msg;
    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);
}

void test() {
    log();
    show(getpid());

    std::string msg = "新建会话";
    if (setsid() < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    show(getpid());
    log();
}

int main() {
    log();
    log("测试不是进程组的首进程建立新会话");
    log();

    if (fork() == 0) {
        test();
        exit(-1);
    }

    sleep(1);
    log("主进程退出");
    log();

    return 0;
}
