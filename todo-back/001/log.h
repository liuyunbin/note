
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <string>

std::string get_time() {
    time_t now = time(NULL);
    struct tm* info = localtime(&now);
    char buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    return buf;
}

void log(const std::string& msg = "") {
    std::cout << get_time() << " " << getpid() << " " << msg << std::endl;
}

using fun_t = void (*)(int sig, siginfo_t*, void*);

// 只捕获 SIGCHLD, 不 waitpid
void handle_signal_1(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
}

// 捕获 SIGCHLD 后, 只 waitpid 处理一次
void handle_signal_2(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    int fd = waitpid(-1, NULL, WNOHANG);
    if (fd > 0) {
        log("已退出的子进程是: " + std::to_string(fd));
    }
}

// 捕获 SIGCHLD 后, 循环 waitpid 直到失败
void handle_signal_3(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    for (;;) {
        int fd = waitpid(-1, NULL, WNOHANG);
        if (fd <= 0) break;
        log("已退出的子进程是: " + std::to_string(fd));
    }
}

void set_signal(const fun_t& f = NULL, int sa_flags = SA_SIGINFO) {
    struct sigaction act;

    if (f == NULL) {
        act.sa_handler = SIG_IGN;
        act.sa_flags = SA_RESTART;
    } else {
        act.sa_sigaction = f;
        act.sa_flags = sa_flags;
    }

    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);
}
