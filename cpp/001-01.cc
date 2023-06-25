
#include "log.h"

int main() {
    log();
    log("操作系统-僵尸进程-产生: 未处理 SIGCHLD");
    log();

    pid_t fd = fork();

    if (fd == 0) {
        log("子进程已启动: " + std::to_string(getpid()));
        for (;;)
            ;
    }
    sleep(1);  // 保证子进程已启动
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(fd);
    log("子进程状态");
    system(cmd.data());
    log("杀死子进程: " + std::to_string(fd));
    kill(fd, SIGKILL);
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
    return 0;
}
