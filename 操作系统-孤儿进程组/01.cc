
#include "log.h"

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
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    for (auto key : m) {
        sigaction(key.first, &act, NULL);
    }
}

int main() {
    init();

    log("测试孤儿进程组");
    log();
    log("设置信号处理");
    set_signal();

    std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
    pid_t main_pid = getpid();
    if (fork() == 0) {
        // 测试的父进程
        log("设置新的进程组 " + std::to_string(getpid()));
        setpgid(getpid(), getpid());
        pid_t child_1 = fork();
        if (child_1 == 0) {
            // 测试的第一个子进程
            log("第一个子进程使自己暂停");
            kill(getpid(), SIGSTOP);
            for (;;)
                ;
        } else if (fork() == 0) {
            // 测试的第二个子进程
            sleep(1);
            log("第二个子进程启动");
            log("进程状态");
            std::string commond = cmd;
            commond += std::to_string(main_pid) + ",";
            commond += std::to_string(child_1) + ",";
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            log("杀死父进程 " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            sleep(1);
            log("进程状态");
            commond = cmd;
            commond += std::to_string(child_1) + ",";
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            log("杀死第一个子进程 " + std::to_string(child_1));
            kill(child_1, SIGKILL);
            log("第二个子进程退出");
            return 0;
        } else {
            // 父进程
            for (;;)
                ;
        }
    }

    sleep(3);
    sleep(3);
    log();
    log("主进程退出");

    return 0;
}
