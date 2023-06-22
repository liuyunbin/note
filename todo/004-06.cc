
#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 ", m[sig]);
    log("处理信号 ", m[sig], " 中...");
    sleep(2);
    log("处理信号 ", m[sig], " 完成");
}

int main() {
    log();
    log("操作系统-信号");
    log("测试信号处理过程中不同的信号到达");
    log();

    log("设置信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程启动");
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 ", m[SIGUSR1]);
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 ", m[SIGUSR2]);
        kill(fd, SIGUSR2);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log();
    log("主进程正常退出");
    log();
    return 0;
}
