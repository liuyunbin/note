
#include "log.h"

int main() {
    log("测试新建会话首进程对应的的进程组");
    log();

    if (fork() == 0) {
        log("原进程信息");
        log(getppid());
        log("创建新会话");
        setsid();
        test(getpid(), getpid());
        exit(-1);
    }
    sleep(1);
    log();
    log("主进程退出");

    return 0;
}
