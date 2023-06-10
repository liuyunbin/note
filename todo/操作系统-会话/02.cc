
#include "log.h"

int main() {
    signal(SIGCHLD, SIG_IGN);

    log("测试不是进程组的首进程建立新会话");
    log();

    if (fork() == 0) {
        test();
        exit(-1);
    }

    sleep(1);
    log();
    log("主进程退出");

    return 0;
}
