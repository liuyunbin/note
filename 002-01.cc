
#include "log.h"

int main() {
    log();
    log("操作系统-孤儿进程");
    log();

    if (fork() == 0) {
        if (fork() == 0) {
            // 测试的子进程
            sleep(1);
            log("测试的子进程(", getpid(), ")启动");
            std::string cmd =
                to_string("ps -o pid,ppid,pgid,sid,state,comm -p ",
                          getpid(),
                          ",",
                          getppid());
            log("进程状态");
            system(cmd.data());
            log("杀死父进程 ", getppid());
            kill(getppid(), SIGKILL);
            sleep(1);
            cmd = to_string("ps -o pid,ppid,pgid,sid,state,comm -p ",
                            getpid(),
                            ",",
                            getppid());
            log("进程状态");
            system(cmd.data());
            return 0;
        } else {
            // 测试的父进程
            log("测试的父进程(", getpid(), ")启动");
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
