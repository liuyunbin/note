
#include "00.h"

int main() {
    log();
    log("测试新建会话首进程对应的的进程组");
    log();

    if (fork() == 0) {
        log("创建新会话");
        setsid();
        test(getpid(), getpid());
        exit(-1);
    }
    sleep(1);
    log("主进程退出");
    log();

    return 0;
}
