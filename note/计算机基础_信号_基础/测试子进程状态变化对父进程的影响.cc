
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
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
    log("信号处理函数-捕获来自 " + std::to_string(sig_info->si_pid) +
        " 的信号 " + m[sig]);
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    for (auto key : m) sigaction(key.first, &act, NULL);
}

int main() {
    init();

    log("测试子进程状态变化对父进程的影响");

    pid_t fd = fork();

    if (fd == 0) {
        // 子进程
        log("子进程启动");
        sleep(5);
        log("子进程退出");
        return 0;
    } else {
        // 父进程
        set_signal();
        log("父进程注册信号处理");
        sleep(1);
        log("发送信号使子进程暂停");
        kill(fd, SIGTSTP);
        sleep(1);
        log("发送信号使子进程继续");
        kill(fd, SIGCONT);
        sleep(1);
        sleep(5);
    }

    log("主进程退出");

    return 0;
}
