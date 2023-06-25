
#include "00.h"

int main() {
    signal(SIGCHLD, SIG_IGN);

    log();
    log("测试会话");
    log();

    log("测试进程组的首进程建立新会话");
    test();

    log("主进程退出");
    log();

    return 0;
}
