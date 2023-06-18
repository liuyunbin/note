
#include "log.h"

int main() {
    log();
    log("操作系统-僵尸进程-预防");
    log("测试设置 SIGCHLD 处理为 SIG_IGN");
    log();

    log("设置 SIGCHLD 的信号处理");
    signal(SIGCHLD, SIG_IGN);

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
