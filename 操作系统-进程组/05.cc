
#include "log.h"

int main() {
    log("测试新建子进程对应的进程组(其他情况)");
    log();

    pid_t child = fork();
    if (child == 0) {
        for (;;)
            ;
    }
    sleep(1);
    log("新建子进程(" + std::to_string(child) + ")的进程组");
    test(child, child);
    kill(child, SIGKILL);

    sleep(1);
    log();
    log("主进程退出");

    return 0;
}
