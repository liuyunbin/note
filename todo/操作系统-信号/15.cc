
#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDSTOP | SA_NOCLDWAIT | SA_RESTART;
    for (auto key : m) sigaction(key.first, &act, NULL);
}

int main() {
    log("测试信号");
    init();

    log();
    log("注册所有信号处理");
    set_signal();

    log("主进程死循环");
    log();
    for (;;)
        ;

    log("主进程退出");

    return 0;
}
