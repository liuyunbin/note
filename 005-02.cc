
#include "log.h"

void handle_signal(int sig) {
    log("测试的父进程捕捉到信号 SIGUSR1");
}

int main() {
    log();
    log("操作系统-进程");
    log("测试不可被信号打断的休眠(指被捕获的信号)");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("测试的父进程注册信号处理函数");
        signal(SIGUSR1, handle_signal);
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
        std::string cmd = to_string("ps -o pid,state,comm -p ", fd);

        log("测试的父进程状态");
        system(cmd.data());

        log("向测试的父进程发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("测试的父进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log();
    log("主进程正常退出");
    log();
    return 0;
}
