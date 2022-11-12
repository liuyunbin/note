
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

jmp_buf buf;

void handle_signal_1(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGABRT");
}

void handle_signal_2(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGABRT");
    longjmp(buf, 1);
}

// type 为 1 表示 SIGABRT 的信号处理函数使用 SIG_DFL
// type 为 2 表示 SIGABRT 的信号处理函数使用 SIG_IGN
// type 为 3 表示 SIGABRT 的信号处理函数使用 handle_signal_1 捕获信号并返回
// type 为 4 表示 SIGABRT 的信号处理函数使用 handle_signal_2 捕获信号不返回
void set_signal(int type = 0) {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    if (type == 1) {
        log("SIGABRT 处理为 SIG_DFL");
        act.sa_handler = SIG_DFL;
    } else if (type == 2) {
        log("SIGABRT 处理为 SIG_IGN");
        act.sa_handler = SIG_IGN;
    } else if (type == 3) {
        log("SIGABRT 处理为 捕获信号并返回");
        act.sa_sigaction = handle_signal_1;
        act.sa_flags = SA_SIGINFO;
    } else {
        log("SIGABRT 处理为 捕获信号不返回");
        act.sa_sigaction = handle_signal_2;
        act.sa_flags = SA_SIGINFO;
    }
    sigaction(SIGABRT, &act, NULL);
}

int main() {
    log("测试信号 SIGABRT");

    for (int i = 1; i < 5; ++i) {
        if (fork() == 0) {
            log();
            set_signal(i);
            if (setjmp(buf) == 0) {
                log("调用 abort()");
                abort();
            }
            log("子进程正常退出");
            exit(-1);
        }
        sleep(1);
    }

    for (int i = 1; i < 5; ++i) {
        if (fork() == 0) {
            log();
            set_signal(i);
            if (setjmp(buf) == 0) {
                log("使用 kill() 发送信号 SIGABRT");
                kill(getpid(), SIGABRT);
            }
            log("子进程正常退出");
            exit(-1);
        }
        sleep(1);
    }

    log();
    log("主进程正常退出");

    return 0;
}
