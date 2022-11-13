
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
}

void set_signal(int flag) {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    if (flag == 0) {
        act.sa_flags = SA_SIGINFO;
    } else {
        log("设置 SA_NOCLDSTOP");
        act.sa_flags = SA_SIGINFO | SA_NOCLDSTOP;
    }
    sigaction(SIGCHLD, &act, NULL);
}

int main() {
    log("测试信号 SIGCHLD, 子进程的暂停和继续");

    for (int i = 0; i < 2; ++i) {
        log();
        set_signal(i);
        pid_t fd = fork();
        if (fd == 0) {
            log("子进程启动");
            sleep(2);
            sleep(2);
            log("子进程正常退出");
            exit(-1);
        } else {
            sleep(1);
            log("使子进程暂停");
            kill(fd, SIGTSTP);
            sleep(1);
            log("使子进程继续");
            kill(fd, SIGCONT);
            sleep(1);
            sleep(5);
        }
    }

    log();
    log("主进程正常退出");

    return 0;
}
