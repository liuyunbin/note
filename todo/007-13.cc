
#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
}

int main() {
    log();
    log("操作系统-信号: 子进程状态变化时, 父进程的处理");
    log();

    log("注册信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    sigaction(SIGCHLD, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        // 子进程
        log("子进程启动");
        sleep(2);
        log("子进程退出");
        return 0;
    } else {
        // 父进程
        sleep(1);
        log("发送信号使子进程暂停");
        kill(fd, SIGTSTP);
        sleep(1);
        log("发送信号使子进程继续");
        kill(fd, SIGCONT);
    }
    sleep(1);
    sleep(1);
    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
