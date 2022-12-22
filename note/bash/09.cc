
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

int main() {
    log("测试信号 SIGABRT 处理为 SIG_IGN");
    log();

    log("设置 SIGABRT 处理为 SIG_IGN");
    signal(SIGABRT, SIG_IGN);
    log("调用 abort()");
    abort();

    sleep(1);

    log();
    log("主进程正常退出");

    return 0;
}
