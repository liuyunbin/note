
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

std::map<int, std::string> m;
void init() {
    m[SIGHUP] = " 1-SIGHUP ";
    m[SIGCHLD] = "17-SIGCHLD";
    m[SIGCONT] = "18-SIGCONT";
}

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    if (sig == SIGCHLD) return;
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO | SA_NOCLDWAIT;
    for (auto key : m) sigaction(key.first, &act, NULL);
}

int main() {
    init();

    log("测试孤儿进程和孤儿进程组");

    log();
    log("设置信号处理");
    set_signal();

    std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
    if (fork() == 0) {
        // 子进程
        log();
        log("测试孤儿进程");
        if (fork() == 0) {
            // 子进程
            std::string commond = cmd;
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            log("进程状态");
            system(commond.data());
            log("杀死父进程 " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            log("进程状态");
            commond = cmd;
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            sleep(1);
            log("子进程退出");
            return 0;
        } else {
            // 父进程
            for (;;)
                ;
            return 0;
        }
    }

    sleep(5);
    sleep(5);

    cmd += std::to_string(getpid()) + ",";
    if (fork() == 0) {
        // 子进程
        log();
        log("测试孤儿进程组");
        log("设置新的进程组 " + std::to_string(getpid()));
        setpgid(getpid(), getpid());
        pid_t child_1 = fork();
        if (child_1 == 0) {
            // 子进程
            log("第一个子进程");
            log("使自己暂停");
            kill(getpid(), SIGSTOP);
            sleep(2);
            log("第一个子进程退出");
            return 0;
        } else if (fork() == 0) {
            // 子进程
            sleep(1);
            log("第二个子进程");
            log("进程状态");
            std::string commond = cmd;
            commond += std::to_string(child_1) + ",";
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            log("杀死父进程 " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(2);
            log("进程状态");
            commond = cmd;
            commond += std::to_string(child_1) + ",";
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            sleep(2);
            sleep(2);
            log("第二个子进程退出");
            return 0;
        } else {
            // 父进程
            for (;;)
                ;
            return 0;
        }
    }

    sleep(6);
    sleep(6);
    log("主进程退出");

    return 0;
}
