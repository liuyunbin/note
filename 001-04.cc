

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    for (;;) {
        int fd = waitpid(-1, NULL, WNOHANG);
        if (fd <= 0) break;
        log("已退出的子进程是: " + std::to_string(fd));
    }
}

int main() {
    log();
    log("测试预防僵尸进程");
    log("测试设置 SIGCHLD 处理为: 循环调用 waitpid()");
    log();

    log("设置 SIGCHLD 的信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;
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
            std::string msg = "第 " + std::to_string(i) + " 个子进程(";
            msg += std::to_string(getpid()) + ")启动后退出";
            log(msg);
            exit(-1);
        } else {
            // 父进程
            cmd += std::to_string(fd) + ",";
            sleep(1);
        }
    }

    cmd.pop_back();  // 删除多余的逗号

    log("解除信号 SIGCHLD 的阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("子进程的状态");
    system(cmd.data());

    log("主进程退出");
    log();

    return 0;
}
