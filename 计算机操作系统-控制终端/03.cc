
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

void handle(int) {
    log("捕获 SIGTTOU");
}

int main() {
    log();
    log("计算机操作系统-控制终端-测试前台进程组修改前台进程组");
    log();

    signal(SIGTTOU, handle);

    int fd = fork();
    if (fd == 0) {
        // 子进程
        fd = getpid();
        setpgid(fd, fd);
        log("子进程的进程组为: " + std::to_string(getpgid(fd)));
        log("父进程的进程组为: " + std::to_string(getpgid(getppid())));
        log("      前台进程组: " + std::to_string(tcgetpgrp(0)));
        log();
        std::string msg = "修改前台进程组";
        if (tcsetpgrp(0, fd) < 0) {
            msg += ": ";
            msg += strerror(errno);
        }
        log(msg);
        log();
        log("子进程的进程组为: " + std::to_string(getpgid(fd)));
        log("父进程的进程组为: " + std::to_string(getpgid(getppid())));
        log("      前台进程组: " + std::to_string(tcgetpgrp(0)));
        return 0;
    }
    sleep(2);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
