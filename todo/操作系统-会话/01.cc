
#include "log.h"

int main() {
    signal(SIGCHLD, SIG_IGN);

    log("测试会话");
    log();

    log("测试进程组的首进程建立新会话");
    test();
    log();

    log("主进程退出");

    return 0;
}
