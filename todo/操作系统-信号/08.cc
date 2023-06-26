

#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <string>

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

int main() {
    log();
    log("操作系统-信号: SIGABRT 处理为 SIG_DFL");
    log();

    log("设置 SIGABRT 处理为 SIG_DFL");
    signal(SIGABRT, SIG_DFL);

    log("调用 abort()");
    abort();

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
