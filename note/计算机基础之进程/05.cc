
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

void handle_signal(int sig) { log("捕捉到信号 SIGUSR1"); }

int main() {
    log("测试 暂停 => 继续");
    log();
    log("注册信号处理函数");
    signal(SIGUSR1, handle_signal);
    pid_t fd = fork();
    std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);
    if (fd == 0) {
        for (;;)
            ;
    } else {
        sleep(2);
        log("使子进程暂停");
        kill(fd, SIGSTOP);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("发送信号 SIGCONT");
        kill(fd, SIGCONT);
        sleep(1);
        log("子进程状态");
        system(cmd.data());
        kill(fd, SIGKILL);
        wait(NULL);
    }

    log();
    log("主进程正常退出");

    return 0;
}
