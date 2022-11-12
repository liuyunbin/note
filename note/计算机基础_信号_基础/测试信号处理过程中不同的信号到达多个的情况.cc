
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <setjmp.h>

std::map<int, std::string> m;
void init() {
    m[SIGHUP   ] = " 1-SIGHUP ";
    m[SIGINT   ] = " 2-SIGINT ";
    m[SIGQUIT  ] = " 3-SIGQUIT";
    m[SIGILL   ] = " 4-SIGILL ";
    m[SIGTRAP  ] = " 5-SIGTRAP";
    m[SIGABRT  ] = " 6-SIGABRT";
    m[SIGBUS   ] = " 7-SIGBUS ";
    m[SIGFPE   ] = " 8-SIGFPE ";
    m[SIGKILL  ] = " 9-SIGKILL";
    m[SIGUSR1  ] = "10-SIGUSR1";
    m[SIGSEGV  ] = "11-SIGSEGV";
    m[SIGUSR2  ] = "12-SIGUSR2";
    m[SIGPIPE  ] = "13-SIGPIPE";
    m[SIGALRM  ] = "14-SIGALRM";
    m[SIGTERM  ] = "15-SIGTERM";
    m[SIGSTKFLT] = "16-SIGSTKF";
    m[SIGCHLD  ] = "17-SIGCHLD";
    m[SIGCONT  ] = "18-SIGCONT";
    m[SIGSTOP  ] = "19-SIGSTOP";
    m[SIGTSTP  ] = "20-SIGTSTP";
    m[SIGTTIN  ] = "21-SIGTTIN";
    m[SIGTTOU  ] = "22-SIGTTOU";
    m[SIGURG   ] = "23-SIGURG ";
    m[SIGXCPU  ] = "24-SIGXCPU";
    m[SIGXFSZ  ] = "25-SIGXFSZ";
    m[SIGVTALRM] = "26-SIGVTAL";
    m[SIGPROF  ] = "27-SIGPROF";
    m[SIGWINCH ] = "28-SIGWINC";
    m[SIGIO    ] = "29-SIGIO  ";
    m[SIGPWR   ] = "30-SIGPWR ";
    m[SIGSYS   ] = "31-SIGSYS ";
}

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() <<  "): " << msg << std::endl;
}

void handle_signal(int sig, siginfo_t* sig_info, void * ) {
    log("信号处理函数-捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
    // 对 SIGUSR1 SIGUSR2 特殊处理
    if (sig == SIGUSR1 || sig == SIGUSR2) {
        log("信号处理函数-处理来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig] + " 中...");
        sleep(1);
        log("信号处理函数-处理来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig] + " 完成");
    }
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    for (auto key : m)
        sigaction(key.first, &act, NULL);
}

int main() {
    log("测试信号处理函数执行过程中, 相同的信号到达多个");

    init();

    log("注册信号处理");
    set_signal();

    pid_t fd = fork();

    if (fd == 0) {
        // 子进程
        sleep(5);
        return 0;
    } else {
        // 父进程
        log("发送信号 " + m[SIGUSR1]);
        kill(fd, SIGUSR1);
        sleep(1);
        for (int i = 1; i < 5; ++i) {
            log("发送信号 " + m[SIGUSR2]);
            kill(fd, SIGUSR2);
        }
    }

    sleep(10);

    log("主进程退出");

    return 0;
}

