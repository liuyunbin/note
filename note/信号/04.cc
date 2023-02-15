
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

int count = 0;

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

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 SIGUSR1 第 " + std::to_string(++count) + " 次");
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    log("设置信号触发后被重置");
    act.sa_flags = SA_SIGINFO | SA_RESETHAND;
    sigaction(SIGUSR1, &act, NULL);
}

int main() {
    log("测试信号处理函数被重置");
    log();
    log("注册信号处理函数");
    set_signal();
    log("发送信号 SIGUSR1 第 1 次");
    kill(getpid(), SIGUSR1);
    sleep(1);
    log("发送信号 SIGUSR1 第 2 次");
    kill(getpid(), SIGUSR1);
    sleep(1);
    log();
    log("主进程退出");

    return 0;
}
