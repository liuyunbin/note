
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

std::map<int, std::string> m;
void init() {
    m[SIGHUP] = " 1-SIGHUP";
    m[SIGINT] = " 2-SIGINT";
    m[SIGQUIT] = " 3-SIGQUIT";
    m[SIGILL] = " 4-SIGILL";
    m[SIGTRAP] = " 5-SIGTRAP";
    m[SIGABRT] = " 6-SIGABRT";
    m[SIGBUS] = " 7-SIGBUS";
    m[SIGFPE] = " 8-SIGFPE";
    m[SIGKILL] = " 9-SIGKILL";
    m[SIGUSR1] = "10-SIGUSR1";
    m[SIGSEGV] = "11-SIGSEGV";
    m[SIGUSR2] = "12-SIGUSR2";
    m[SIGPIPE] = "13-SIGPIPE";
    m[SIGALRM] = "14-SIGALRM";
    m[SIGTERM] = "15-SIGTERM";
    m[SIGSTKFLT] = "16-SIGSTKFLT";
    m[SIGCHLD] = "17-SIGCHLD";
    m[SIGCONT] = "18-SIGCONT";
    m[SIGSTOP] = "19-SIGSTOP";
    m[SIGTSTP] = "20-SIGTSTP";
    m[SIGTTIN] = "21-SIGTTIN";
    m[SIGTTOU] = "22-SIGTTOU";
    m[SIGURG] = "23-SIGURG";
    m[SIGXCPU] = "24-SIGXCPU";
    m[SIGXFSZ] = "25-SIGXFSZ";
    m[SIGVTALRM] = "26-SIGVTALRM";
    m[SIGPROF] = "27-SIGPROF";
    m[SIGWINCH] = "28-SIGWINCH";
    m[SIGIO] = "29-SIGIO";
    m[SIGPWR] = "30-SIGPWR";
    m[SIGSYS] = "31-SIGSYS";
}

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    std::string msg = sig == SIGUSR1 ? "SIGUSR1" : "SIGUSR2";
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + msg);
    log("处理来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + msg + " 中...");
    sleep(2);
    log("处理来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + msg + " 完成");
}

void set_signal(bool block = false) {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    if (block) {
        log("设置信号处理过程中阻塞 SIGUSR2");
        sigaddset(&act.sa_mask, SIGUSR2);
    }
    act.sa_flags = SA_SIGINFO|SA_NOCLDWAIT|SA_NOCLDSTOP;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
}

int main() {
    log("测试信号处理过程中信号到达");
    init();

    log();
    log("测试信号处理过程中相同信号到达");
    log("设置信号处理函数");
    set_signal();
    pid_t fd = fork();
    if (fd == 0) {
        log("子进程启动");
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log();
    log("测试信号处理过程中不同信号到达");
    log("设置信号处理函数");
    set_signal();
    fd = fork();
    if (fd == 0) {
        log("子进程启动");
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 SIGUSR2");
        kill(fd, SIGUSR2);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log();
    log("测试信号处理过程中阻塞其他信号");
    log("设置信号处理函数");
    set_signal(true);
    fd = fork();
    if (fd == 0) {
        log("子进程启动");
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 SIGUSR2");
        kill(fd, SIGUSR2);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log("主进程退出");

    return 0;
}
