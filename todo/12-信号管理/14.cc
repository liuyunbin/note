

#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <string>

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
}

int main() {
    log();
    log("计算机操作系统-信号: 子进程状态变化时, 父进程的处理");
    log("不接收子进程暂停继续产生的 SIGCHLD");
    log();

    log("注册信号处理");
    log("设置不接受子进程暂停继续产生的 SIGCHLD");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        // 子进程
        log("子进程启动");
        sleep(2);
        log("子进程退出");
        return 0;
    } else {
        // 父进程
        sleep(1);
        log("发送信号使子进程暂停");
        kill(fd, SIGTSTP);
        sleep(1);
        log("发送信号使子进程继续");
        kill(fd, SIGCONT);
    }
    sleep(1);
    sleep(1);
    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
