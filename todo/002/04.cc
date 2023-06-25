
#include "log.h"

int main() {
    log();
    log("测试不可被信号打断的休眠(指被捕获的信号) 对 SIGKILL 的处理");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        if (vfork() == 0) {
            log("测试的子进程启动");
            log("测试的子进程休眠10秒");
            sleep(10);
            log("测试的子进程休眠完成");
            log("测试的子进程退出");
            exit(-1);
        }
        log("测试的父进程休眠1s");
        sleep(1);
        log("测试的父进程退出");
        exit(-1);
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("测试的父进程状态");
        system(cmd.data());

        log("向测试的父进程发送信号 SIGKILL");
        kill(fd, SIGKILL);
        sleep(1);
        log("测试的父进程状态");
        system(cmd.data());
        wait(NULL);
    }

    sleep(10);
    log("主进程正常退出");
    log();

    return 0;
}
