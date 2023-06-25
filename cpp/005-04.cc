
#include "log.h"

int main() {
    log();
    log("操作系统-进程组: 新建子进程对应的进程组(子进程调用exec之后)");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程调用exec");
        execl("/usr/bin/sleep", "sleep", "3", NULL);
        log("子进程失败");
        exit(-1);
    }
    sleep(1);
    log("新建子进程的进程组: " + std::to_string(fd));
    test_pgid(fd, fd);
    kill(fd, SIGKILL);

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
