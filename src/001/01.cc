
#include "log.h"

int main() {
    log("测试僵尸进程");
    log("测试父进程未处理子进程退出的状态信息");
    log();

    pid_t child = fork();

    if (child == 0) {
        // 子进程
        log("子进程已启动");
        for (;;)
            ;
    }
    sleep(1);  // 保证子进程已启动
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(child);
    log("子进程状态");
    system(cmd.data());
    log("杀死子进程 " + std::to_string(child));
    kill(child, SIGKILL);
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log();
    log("主进程退出");

    return 0;
}
