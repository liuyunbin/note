#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <map>

void log(const std::string& msg) {
    std::cout << "进程(" << getpid() <<  "): " << msg << std::endl;
}

void handle_signal(int sig, siginfo_t* sig_info, void * ) {
    log("信号处理函数-捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    log("已退出的子进程是: " + std::to_string(waitpid(-1, NULL, 0)));
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGCHLD, &act, NULL);
}

void handle_signal_2(int sig, siginfo_t* sig_info, void * ) {
    log("信号处理函数-捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    for (;;) {
        int fd = waitpid(-1, NULL, WNOHANG);
        if (fd <= 0)
            break;
        log("已退出的子进程是: " + std::to_string(fd));
    }
}

void set_signal_2() {
    struct sigaction act;
    act.sa_sigaction = handle_signal_2;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGCHLD, &act, NULL);
}

void set_signal_3() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO | SA_NOCLDWAIT;
    sigaction(SIGCHLD, &act, NULL);
}
int main() {
    log("测试僵尸进程");

    log("");
    log("测试子进程已退出, 父进程未处理的情况");
    pid_t fd = fork();

    if (fd == 0) {
        // 子进程
        log("子进程启动");
        log("子进程退出");
        return 0;
    } else {
        // 父进程
        sleep(1);
        log("子进程状态");
        std::string cmd = "ps -o pid,ppid,state -p " + std::to_string(fd);
        system(cmd.data());
        waitpid(-1, NULL, 0); // 捕捉子进程 和 system
        waitpid(-1, NULL, 0);
    }

    log("");
    log("测试子进程已退出, 父进程未正确处理的情况");
    set_signal();
    for (int i = 0; i < 5; ++i) {
        fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动");
            return 0;
        }
    }
    // 父进程
    sleep(1);
    log("子进程状态");
    std::string cmd = "ps -o pid,ppid,state,comm -C a.out,ps";
    system(cmd.data());

    sleep(1);

    log("");
    log("测试子进程已退出, 父进程正确处理的情况");
    set_signal_2();
    for (int i = 0; i < 5; ++i) {
        fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动");
            return 0;
        }
    }
    // 父进程
    log("子进程状态");
    system(cmd.data());
    sleep(1);
    sleep(1);
    sleep(1);
    sleep(1);
    sleep(1);
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log("");
    log("使用 sigaction 简化对僵尸进程的处理");
    set_signal_3();
    for (int i = 0; i < 5; ++i) {
        fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动");
            return 0;
        }
    }
    // 父进程
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log("");
    log("使用 signal 简化对僵尸进程的处理");
    signal(SIGCHLD, SIG_IGN);
    for (int i = 0; i < 5; ++i) {
        fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动");
            return 0;
        }
    }
    // 父进程
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    return 0;
}

