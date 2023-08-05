
#include "log.h"

int main() {
    log();
    log("操作系统-信号: SIGABRT 处理为 SIG_DFL");
    log();

    log("设置 SIGABRT 处理为 SIG_DFL");
    signal(SIGABRT, SIG_DFL);

    log("调用 abort()");
    abort();

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
