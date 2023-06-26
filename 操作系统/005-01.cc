
#include "log.h"

int main() {
    log();
    log("操作系统-进程组: 新建自身进程对应的进程组");
    log();

    test_pgid(getpid(), getpid());
    if (fork() == 0) {
        test_pgid(getpid(), getpid());
        exit(-1);
    }
    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
