
#include "log.h"

int main() {
    log();
    log("操作系统-孤儿进程");
    log();

    if (fork() == 0) {
        if (fork() == 0) {
            // 测试的子进程
            sleep(1);
            log("测试的子进程(" + std::to_string(getpid()) + ")启动");
            std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
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
            return 0;
        } else {
            // 测试的父进程
            log("测试的父进程(" + std::to_string(getpid()) + ")启动");
            for (;;)
                ;
        }
    }

    sleep(3);

    log("主进程退出");
    log();

    return 0;
}
