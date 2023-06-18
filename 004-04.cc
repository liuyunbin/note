
#include "log.h"

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
int count = 0;

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 SIGUSR1 第 " + std::to_string(++count) + " 次");
}

int main() {
    log();
    log("测试信号处理函数被重置");
    log();

    log("注册信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);

    log("设置信号触发后被重置");
    act.sa_flags = SA_SIGINFO | SA_RESETHAND;
    sigaction(SIGUSR1, &act, NULL);

    log("发送信号 SIGUSR1 第 1 次");
    kill(getpid(), SIGUSR1);
    sleep(1);
    log("发送信号 SIGUSR1 第 2 次");
    kill(getpid(), SIGUSR1);

    sleep(1);
    log("主进程退出");
    log();

    return 0;
}
