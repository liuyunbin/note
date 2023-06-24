
#include "log.h"

int main() {
    log();
    log("操作系统-进程组");
    log("测试新建子进程对应的进程组(子进程属于不同的会话)");
    log();

    pid_t child = fork();
    if (child == 0) {
        log("子进程新建会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("父进程会话: ", getsid(getpid()));
    log("子进程会话: ", getsid(child));
    log("新建子进程(", child, ")的进程组");
    test_pgid(child, child);
    kill(child, SIGKILL);

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
