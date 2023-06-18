
#include "log.h"

int main() {
    log();
    log("操作系统-进程组");
    log("测试新建自身进程对应的进程组");
    log();

    test_pgid(getpid(), getpid());
    if (fork() == 0) {
        test_pgid(getpid(), getpid());
        exit(-1);
    }
    sleep(1);
    log("主进程退出");
    log();

    return 0;
}
