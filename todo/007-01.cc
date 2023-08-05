
#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
}

int main() {
    log();
    log("操作系统-信号-阻塞");
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

    log("发送除 " + m[SIGKILL] + " 和 " + m[SIGSTOP] + " 外的所有信号");

    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP)
            kill(getpid(), key.first);

    log("查看待决的信号");
    sigset_t new_mask;
    sigpending(&new_mask);
    for (auto key : m)
        if (sigismember(&new_mask, key.first))
            log("待决的信号: " + m[key.first]);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
