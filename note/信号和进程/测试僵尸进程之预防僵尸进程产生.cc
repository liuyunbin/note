
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    for (;;) {
        int fd = waitpid(-1, NULL, WNOHANG);
        if (fd <= 0) break;
        log("已退出的子进程是: " + std::to_string(fd));
    }
}

void set_signal(int type) {
    struct sigaction act;

    switch (type) {
        case 0:
            log("测试信号 SIGCHLD 处理为: SIG_IGN");
            act.sa_handler = SIG_IGN;
            act.sa_flags = SA_RESTART;
            break;
        case 1:
            log("测试信号 SIGCHLD 处理为: 循环调用 waitpid()");
            act.sa_sigaction = handle_signal;
            act.sa_flags = SA_RESTART | SA_SIGINFO;
            break;
        case 2:
            log("测试信号 SIGCHLD 处理为: 设置 SA_NOCLDWAIT");
            act.sa_handler = SIG_DFL;
            act.sa_flags = SA_RESTART | SA_NOCLDWAIT;
            break;
    }

    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);
}

void test_SIGCHLD() {
    std::string cmd = "ps -o pid,comm,state -p ";

    log("阻塞信号 SIGCHLD");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    for (int i = 1; i <= 3; ++i) {
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            log("第 " + std::to_string(i) + " 个子进程启动后退出");
            exit(-1);
        } else {
            // 父进程
            cmd += std::to_string(fd) + ",";
            sleep(1);
        }
    }

    cmd.pop_back();

    log("解除信号 SIGCHLD 的阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("此时, 子进程的状态");
    system(cmd.data());
}

int main() {
    log("测试僵尸进程之预防僵尸进程的产生");

    for (int i = 0; i < 3; ++i) {
        log();
        set_signal(i);
        test_SIGCHLD();
    }

    log("主进程退出");

    return 0;
}
