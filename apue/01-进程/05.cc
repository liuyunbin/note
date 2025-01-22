
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

void handle_signal(int sig) {
    log("子进程捕捉到信号 SIGUSR1");
}

int main() {
    log();
    log("操作系统-进程: 暂停 => 继续");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程注册信号处理函数");
        signal(SIGUSR1, handle_signal);
        for (;;)
            ;
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("使子进程暂停");
        kill(fd, SIGSTOP);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGCONT");
        kill(fd, SIGCONT);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGKILL");
        kill(fd, SIGKILL);
        sleep(1);
        log("子进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log();
    log("主进程正常退出");
    log();
    return 0;
}
