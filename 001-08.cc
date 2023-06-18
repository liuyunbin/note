
#include "log.h"

int main() {
    log();
    log("操作系统-僵尸进程-测试");
    log();
    pid_t child = fork();

    if (child == 0) {
        exit(0);
    }
    sleep(1);  // 保证子进程已启动并退出
    log("产生僵尸进程(" + std::to_string(child) + ")");
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(child);
    system(cmd.data());

    log("死循环...");
    for (;;)
        ;

    return 0;
}
