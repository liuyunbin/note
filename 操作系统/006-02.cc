
#include "log.h"

int main() {
    log();
    log("操作系统-会话-新建: 不是进程组的首进程建立新会话");
    log();

    if (fork() == 0) {
        test_sid();
        exit(-1);
    }

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
