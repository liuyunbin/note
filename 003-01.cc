
#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 ", sig_info->si_pid, " 的信号 ", m[sig]);
}

int main() {
    log();
    log("操作系统-孤儿进程组");
    log();

    log("设置信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGHUP, &act, NULL);
    sigaction(SIGCONT, &act, NULL);

    pid_t main_pid = getpid();
    if (fork() == 0) {
        // 测试的父进程
        log("测试的父进程(", getpid(), ")启动");
        log("设置新的进程组(", getpid(), ")");
        setpgid(getpid(), getpid());
        pid_t child_1 = fork();
        if (child_1 == 0) {
            // 测试的第一个子进程
            log("测试的第一个子进程(", getpid(), ")启动");
            log("测试的第一个子进程使自己暂停");
            kill(getpid(), SIGSTOP);
            for (;;)
                ;
        } else if (fork() == 0) {
            // 测试的第二个子进程
            sleep(1);
            log("测试的第二个子进程(", getpid(), ")启动");
            log("进程状态");
            std::string cmd =
                to_string("ps -o pid,ppid,pgid,sid,state,comm -p ",
                          main_pid,
                          ",",
                          child_1,
                          ",",
                          getpid(),
                          ",",
                          getppid());
            log("进程状态");
            system(cmd.data());
            log("杀死测试的父进程(", getppid(), ")");
            kill(getppid(), SIGKILL);
            sleep(1);
            sleep(1);
            cmd = to_string("ps -o pid,ppid,pgid,sid,state,comm -p ",
                            main_pid,
                            ",",
                            child_1,
                            ",",
                            getpid(),
                            ",",
                            getppid());
            log("进程状态");
            system(cmd.data());
            log("杀死测试的第一个子进程(", child_1, ")");
            kill(child_1, SIGKILL);
            log("测试的第二个子进程退出");
            return 0;
        } else {
            // 父进程
            for (;;)
                ;
        }
    }

    sleep(3);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
