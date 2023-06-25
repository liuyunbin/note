
#include "log.h"

int main() {
    log();
    log("操作系统-进程组: 新建子进程对应的进程组(子进程属于不同的会话)");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程新建会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("父进程会话: " + std::to_string(getsid(getpid())));
    log("子进程会话: " + std::to_string(getsid(fd)));
    log("新建子进程的进程组: " + std::to_string(fd));
    test_pgid(fd, fd);
    kill(fd, SIGKILL);

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
