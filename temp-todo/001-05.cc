
#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 ", sig_info->si_pid, " 的信号 SIGCHLD");
}

int main() {
    log();
    log("操作系统-僵尸进程-预防");
    log("测试设置 SIGCHLD 处理为: 设置 SA_NOCLDWAIT");
    log();

    log("设置 SIGCHLD 的信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    act.sa_flags     = SA_SIGINFO | SA_NOCLDWAIT;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    log("阻塞信号 SIGCHLD");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    std::string cmd = "ps -o pid,comm,state -p ";

    for (int i = 1; i <= 5; ++i) {
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            log("第 ", i, " 个子进程(", getpid(), ")启动后退出");
            exit(-1);
        } else {
            // 父进程
            cmd += to_string(fd, ",");
            sleep(1);
        }
    }

    cmd.pop_back();  // 删除多余的逗号

    log("解除信号 SIGCHLD 的阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("子进程的状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
    return 0;
}
