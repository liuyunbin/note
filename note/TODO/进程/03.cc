
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
    log("测试不可被信号打断的休眠(指被捕获的信号) 对 SIGSTOP 的处理");
    log();
    log("注册信号处理函数");
    signal(SIGUSR1, handle_signal);
    pid_t fd = fork();
    std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);
    if (fd == 0) {
        if (vfork() == 0) {
            log("子进程启动");
            system("date +%T");
            log("休眠10秒");
            sleep(10);
            system("date +%T");
            exit(-1);
        }
        sleep(1);
        exit(-1);
    } else {
        sleep(2);
        log("子进程状态");
        system(cmd.data());
        log("发送信号 SIGSTOP");
        kill(fd, SIGSTOP);
        log("子进程状态");
        system(cmd.data());
        log("发送信号 SIGCONT");
        kill(fd, SIGCONT);
        log("子进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log();
    log("主进程正常退出");

    return 0;
}
