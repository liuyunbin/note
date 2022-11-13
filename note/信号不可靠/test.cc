
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

int count = 0;

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 SIGUSR1 第 " + std::to_string(++count) + " 次");
}

void set_signal(bool reset = false) {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    if (reset)
        act.sa_flags = SA_SIGINFO | SA_RESETHAND;
    else
        act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
}

int main() {
    log("测试信号不可靠");

    log();
    log("测试信号丢失");

    log("注册信号 SIGUSR1 处理函数");
    set_signal();

    log("阻塞信号 SIGUSR1");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    for (int i = 1; i <= 5; ++i) {
        log("发送信号 SIGUSR1 第 " + std::to_string(i) + " 次");
        kill(getpid(), SIGUSR1);
    }

    log("解除信号 SIGUSR1 阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    sleep(1);

    log();
    log("重置信号处理函数的计数器");
    count = 0;

    log();
    log("测试信号处理函数被重置");
    log("注册信号 SIGUSR1 处理函数, 并设置重置信号处理");
    set_signal(true);

    log("发送信号 SIGUSR1 第 1 次");
    kill(getpid(), SIGUSR1);
    sleep(1);
    log("发送信号 SIGUSR1 第 2 次");
    kill(getpid(), SIGUSR1);
    sleep(1);
    log("主进程退出");

    return 0;
}
