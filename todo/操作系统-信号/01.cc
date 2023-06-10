
#include "log.h"

int main() {
    init();

    log("测试信号阻塞");
    log();

    log("阻塞所有信号");
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    log("查看被阻塞的信号");
    sigset_t old_mask;
    sigprocmask(SIG_SETMASK, NULL, &old_mask);

    for (auto key : m)
        if (sigismember(&old_mask, key.first))
            log("已被阻塞的信号: " + m[key.first]);

    log();
    log("发送除 " + m[SIGKILL] + " 和 " + m[SIGSTOP] + " 外的所有信号");
    log();

    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP)
            kill(getpid(), key.first);

    sigset_t new_mask;
    sigpending(&new_mask);
    for (auto key : m)
        if (sigismember(&new_mask, key.first))
            log("待决的信号: " + m[key.first]);

    log();
    log("主进程退出");

    return 0;
}
