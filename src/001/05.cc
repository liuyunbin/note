
#include "00.h"

int count = 0;

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 " + m[sig] + " 第 " + std::to_string(++count) + " 次");
    log("处理信号 " + m[sig] + " 中...");
    sleep(2);
    log("处理信号 " + m[sig] + " 完成");
}

int main() {
    init();

    log();
    log("测试信号处理过程中相同的信号到达");
    log();

    log("设置信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程启动");
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 " + m[SIGUSR1] + " 第 1 次");
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 " + m[SIGUSR1] + " 第 2 次");
        kill(fd, SIGUSR1);
        log("发送信号 " + m[SIGUSR1] + " 第 3 次");
        kill(fd, SIGUSR1);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log("主进程退出");
    log();

    return 0;
}
