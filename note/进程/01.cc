
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

std::string get_time() {
    time_t now = time(NULL);
    struct tm* info = localtime(&now);
    char buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", info);
    return buf;
}

void log(const std::string& msg = "") {
    std::cout << get_time() << " " << getpid() << " " << msg << std::endl;
}

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
        log("休眠10秒");
        system("date +%T");
        sleep(10);
        system("date +%T");
        exit(-1);
    } else {
        sleep(2);
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
