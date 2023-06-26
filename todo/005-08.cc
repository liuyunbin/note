
#include "log.h"

int main() {
    log();
    log("操作系统-进程组: 测试修改进程组(原进程组和目标进程组属于不同会话)");
    log();

    pid_t child = fork();

    if (child == 0) {
        log("子进程创建新会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("子进程的状态信息");
    test_pgid(getpid(), child);
    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
