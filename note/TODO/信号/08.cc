
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

std::string get_time() {
    time_t now = time(NULL);
    struct tm* info = localtime(&now);
    char buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", info);
    return buf;
}

void log(const std::string& msg = "") {
    std::cout << get_time() << " " << getpid() << " " << msg << std::endl;
}

int main() {
    log("测试信号 SIGABRT 处理为 SIG_DFL");
    log();

    log("设置 SIGABRT 处理为 SIG_DFL");
    signal(SIGABRT, SIG_DFL);
    log("调用 abort()");
    abort();

    sleep(1);

    log();
    log("主进程正常退出");

    return 0;
}
