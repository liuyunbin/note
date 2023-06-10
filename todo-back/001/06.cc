
#include "log.h"

int main() {
    log("测试预防僵尸进程");
    log("测试杀死父进程");
    log();

    if (fork() == 0) {
        pid_t child = fork();
        std::string cmd = "ps -o pid,ppid,comm,state -p ";
        cmd += std::to_string(child);
        if (child == 0) {
            // 测试的子进程
            log("子进程启动");
            for (;;)
                ;
        } else if (fork() == 0) {
            // 测试的控制进程
            log("控制进程启动");
            sleep(1);
            log("子进程状态");
            system(cmd.data());
            log("杀死父进程 " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            log("子进程状态");
            system(cmd.data());
            log("杀死子进程");
            kill(child, SIGKILL);
            sleep(1);
            log("子进程状态");
            system(cmd.data());
            exit(-1);
        } else {
            // 测试的父进程
            log("父进程启动");
            for (;;)
                ;
        }
    }

    sleep(4);

    log();
    log("主进程退出");

    return 0;
}
