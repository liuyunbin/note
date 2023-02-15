
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
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

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGFPE");
}

void set_signal() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGFPE, &act, NULL);
}

int main() {
    log("测试信号 SIGFPE 处理为 捕获信号并返回");
    log();
    log("设置 SIGFPE 处理为 捕获信号并返回");
    set_signal();
    log("整数除以 0");
    int a = 0;
    int b = 1 / a;
    sleep(1);
    log();
    log("主进程正常退出");

    return 0;
}
