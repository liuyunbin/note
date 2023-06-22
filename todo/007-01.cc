
#include "log.h"

int main() {
    log();
    log("操作系统-会话-新建");
    log();

    log("测试进程组的首进程建立新会话");
    test_sid();

    log();
    log("主进程正常退出");
    log();
    return 0;
}
