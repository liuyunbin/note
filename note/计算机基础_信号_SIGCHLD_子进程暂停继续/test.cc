
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

void handle_signal(int sig) {}

void handle_signal_1(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
}

void handle_signal_2(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    int fd = waitpid(-1, NULL, WNOHANG);
    if (fd > 0) log("已退出的子进程是: " + std::to_string(fd));
}

void handle_signal_3(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    for (;;) {
        int fd = waitpid(-1, NULL, WNOHANG);
        if (fd <= 0) break;
        log("已退出的子进程是: " + std::to_string(fd));
    }
}

// type 为 1 表示信号处理函数使用 SIG_DFL
// type 为 2 表示信号处理函数使用 SIG_IGN
// type 为 3 表示信号处理函数捕获信号, 不处理, 然后返回
// type 为 4 表示信号处理函数捕获信号, 执行 waitpid(), 然后返回
// type 为 5 表示信号处理函数捕获信号, 循环执行 waitpid(), 然后返回
// flag 为 0 不设置
// flag 为 1 设置 SA_NOCLDSTOP
//           不接收由于子进程暂停 停止 后台进程读写终端时产生的信号 SIGCHLD
// flag 为 2 设置 SA_NOCLDWAIT
//           子进程退出时, 不变成僵尸进程
// flag 为 3 设置 SA_NOCLDSTOP 和 SA_NOCLDWAIT
void set_signal(int type, int flag) {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    if (type == 1) {
        log("SIGCHLD 处理为 SIG_DFL");
        act.sa_handler = SIG_DFL;
    } else if (type == 2) {
        log("SIGCHLD 处理为 SIG_IGN");
        act.sa_handler = SIG_IGN;
    } else if (type == 3) {
        log("SIGCHLD 处理为: 捕获信号, 返回");
        act.sa_sigaction = handle_signal_1;
        act.sa_flags |= SA_SIGINFO;
    } else if (type == 4) {
        log("SIGCHLD 处理为: 捕获信号, 执行 waitpid() 一次, 返回");
        act.sa_sigaction = handle_signal_2;
        act.sa_flags |= SA_SIGINFO;
    } else {
        log("SIGCHLD 处理为: 捕获信号, 执行 waitpid() 循环, 返回");
        act.sa_sigaction = handle_signal_3;
        act.sa_flags |= SA_SIGINFO;
    }

    if (flag == 0) {
        // empty
    } else if (flag == 1) {
        log("设置 SA_NOCLDSTOP");
        act.sa_flags |= SA_NOCLDSTOP;
    } else if (flag == 2) {
        log("设置 SA_NOCLDWAIT");
        act.sa_flags |= SA_NOCLDWAIT;
    } else {
        log("设置 SA_NOCLDSTOP 和 SA_NOCLDWAIT");
        act.sa_flags |= SA_NOCLDSTOP;
        act.sa_flags |= SA_NOCLDWAIT;
    }

    sigaction(SIGCHLD, &act, NULL);
}

int main() {
    log("测试信号 SIGCHLD");

    signal(SIGWINCH, handle_signal);

    for (int i = 1; i < 6; ++i)
        for (int j = 0; j < 1; ++j) {
            log();
            pid_t fd = fork();
            std::string cmd = "ps -o pid,state -p " + std::to_string(fd);
            if (fd == 0) {
                // log("子进程启动");
                pause();
                kill(getppid(), SIGWINCH);

                // log("等待暂停");
                sleep(10);
                kill(getppid(), SIGWINCH);

                // log("等待退出");
                pause();
                kill(getppid(), SIGWINCH);
                // log("子进程退出");
                exit(-1);
            } else {
                pid_t ffd = fork();
                if (ffd == 0) {
                    // sleep(10);
                    // system(cmd.data());
                    // kill(getppid(), SIGWINCH);

                    // sleep(10);
                    // system(cmd.data());
                    // kill(getppid(), SIGWINCH);

                    // sleep(10);
                    // system(cmd.data());
                    // kill(getppid(), SIGWINCH);

                    sleep(10);
                    system(cmd.data());
                    kill(getppid(), SIGWINCH);

                    sleep(10);
                    exit(-1);
                }

                set_signal(i, j);

                log("让子进程启动");
                kill(fd, SIGWINCH);
                pause();

                // log("子进程状态");
                // kill(ffd, SIGWINCH);
                // pause();

                log("使子进程暂停");
                kill(fd, SIGTSTP);
                sleep(1);

                // log("子进程状态");
                // kill(ffd, SIGWINCH);
                // pause();

                log("使子进程继续");
                kill(fd, SIGCONT);
                kill(fd, SIGWINCH);
                pause();

                // log("子进程状态");
                // kill(ffd, SIGWINCH);
                // pause();

                log("使子进程退出");
                kill(fd, SIGWINCH);
                pause();

                sleep(1);

                log("子进程状态");
                kill(ffd, SIGWINCH);
                pause();
            }
        }

    sleep(5);
    log();
    log("主进程正常退出");

    return 0;
}
