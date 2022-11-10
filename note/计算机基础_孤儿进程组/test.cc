#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <map>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() <<  "): " << msg << std::endl;
}

std::map<int, std::string> m;
void init() {
    m[SIGHUP   ] = " 1-SIGHUP ";
    m[SIGCONT  ] = "18-SIGCONT";
    m[SIGTSTP  ] = "20-SIGTSTP";
    m[SIGTTIN  ] = "21-SIGTTIN";
    m[SIGTTOU  ] = "22-SIGTTOU";
}

void handle_signal(int sig, siginfo_t* sig_info, void * ) {
    log("信号处理函数-捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO | SA_NOCLDWAIT;
    for (auto key : m)
        sigaction(key.first, &act, NULL);
}

int main() {
    init();

    log("测试孤儿进程");

    if (fork() == 0) {
        // 子进程
        log();
        log("测试孤儿进程处于运行状态");
        if (fork() == 0) {
            // 子进程
            set_signal();
            log("子进程启动");
            log("子进程状态");
            std::string cmd = "ps -o pid,ppid,state -p " + std::to_string(getpid());
            system(cmd.data());
            sleep(2);
            log("子进程状态");
            system(cmd.data());
            sleep(2);
            for(;;)
                ;
            log("子进程退出");
            return 0;
        } else {
            // 父进程
            sleep(1);
            log("父进程退出");
            return 0;
        }
    }

    return 0;
    sleep(5);

    if (fork() == 0) {
        // 子进程
        log();
        log("测试孤儿进程处于暂停状态");
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            set_signal();
            log("子进程启动");
            log("子进程状态");
            std::string cmd = "ps -o pid,ppid,state -p " + std::to_string(getpid());
            system(cmd.data());
            log("子进程使自己暂停");
            kill(getpid(), SIGSTOP);
            sleep(2);
            log("子进程状态");
            system(cmd.data());
            for (;;)
                ;
            log("子进程退出");
            return 0;
        } else {
            // 父进程
            sleep(3);
            log("子进程状态");
            std::string cmd = "ps -o pid,ppid,state -p " + std::to_string(fd);
            system(cmd.data());
            log("父进程退出");
            return 0;
        }
    }

    sleep(1);
    sleep(10);
    log("主进程退出");

    return 0;
}

