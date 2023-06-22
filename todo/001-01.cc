
#include "log.h"

int main() {
    log();
    log("操作系统-僵尸进程-产生");
    log("测试父进程未处理子进程退出的状态信息");
    log();

    pid_t child = fork();

    if (child == 0) {
        log("子进程(", getpid(), ")已启动");
        for (;;)
            ;
    }
    sleep(1);  // 保证子进程已启动
    std::string cmd = to_string("ps -o pid,comm,state -p ", child);
    log("子进程状态");
    system(cmd.data());
    log("杀死子进程(", child, ")");
    kill(child, SIGKILL);
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
    return 0;
}
