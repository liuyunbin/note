
#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 ", sig_info->si_pid, " 的信号 SIGFPE");
}

int main() {
    log();
    log("操作系统-信号");
    log("测试信号 SIGFPE 处理为 捕获信号并返回");
    log();

    log("设置 SIGFPE 处理为 捕获信号并返回");
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags     = SA_SIGINFO;
    sigaction(SIGFPE, &act, NULL);

    log("整数除以 0");
    int a = 0;
    int b = 1 / a;
    log(b);

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}