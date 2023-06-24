
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
    log("产生僵尸进程(", child, ")");
    std::string cmd = to_string("ps -o pid,comm,state -p ", child);
    system(cmd.data());

    log("死循环...");
    for (;;)
        ;

    log();
    log("主进程正常退出");
    log();
    return 0;
}
