
#include "log.h"

void handle_signal(int sig) { log("捕捉到信号 SIGUSR1"); }

int main() {
    log("测试可被信号打断的休眠(指被捕获的信号)");
    log();
    log("注册信号处理函数");
    signal(SIGUSR1, handle_signal);
    pid_t fd = fork();
    std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);
    if (fd == 0) {
        log("子进程启动");
        log("子进程休眠10秒");
        sleep(10);
        log("子进程休眠完成");
        exit(-1);
    } else {
        sleep(1);
        log("子进程状态");
        system(cmd.data());
        log("发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        wait(NULL);
    }

    log();
    log("主进程正常退出");

    return 0;
}
