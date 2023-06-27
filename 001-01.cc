
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "log.h"

int main() {
    log();
    log("计算机操作系统-僵尸进程");
    log("重现僵尸进程的产生: 父进程未处理子进程退出的状态信息");
    log();

    pid_t fd = fork();

    if (fd == 0) {
        log("子进程已启动: ", getpid());
        for (;;)
            ;
    }
    sleep(1);  // 保证子进程已启动
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(fd);
    log("子进程状态");
    system(cmd.data());
    log("杀死子进程:", fd);
    kill(fd, SIGKILL);
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
    return 0;
}
