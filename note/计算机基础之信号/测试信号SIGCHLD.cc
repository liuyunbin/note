
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
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
}

void handle_signal_1(int sig) { log("捕获信号 SIGCHLD"); }

void handle_signal_2(int sig) {
    log("捕获信号 SIGCHLD");
    int fd = waitpid(-1, NULL, WNOHANG);
    if (fd > 0) log("已退出的子进程是: " + std::to_string(fd));
}

void handle_signal_3(int sig) {
    log("捕获信号 SIGCHLD");
    for (;;) {
        int fd = waitpid(-1, NULL, WNOHANG);
        if (fd <= 0) break;
        log("已退出的子进程是: " + std::to_string(fd));
    }
}

void set_signal(int flag = 0) {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    if (flag == 1) {
        log("设置不接受子进程暂停继续产生的 SIGCHLD");
        act.sa_flags |= SA_NOCLDSTOP;
    }
    sigaction(SIGCHLD, &act, NULL);
}

int main() {
    log("测试信号 SIGCHLD");
    init();

    log();
    log("测试子进程暂停 继续 退出时, 向父进程发送 SIGCHLD, 父进程的处理");

    for (int i = 0; i < 2; ++i) {
        log();
        log("注册信号处理");
        set_signal(i);
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
            sleep(1);
            sleep(2);
            wait(NULL);
        }
    }

    std::string cmd = "ps -o pid,comm,state -C a.out";
    sigset_t mask;
    sigfillset(&mask);

    log();
    log("测试父进程 SIGCHLD => SIG_DFL");
    signal(SIGCHLD, SIG_DFL);
    log("阻塞所有信号");
    sigprocmask(SIG_SETMASK, &mask, NULL);
    for (int i = 1; i <= 5; ++i)
        if (fork() == 0) {
            log("第 " + std::to_string(i) + " 个子进程启动并退出");
            exit(-1);
        } else {
            sleep(1);
        }

    log("解除信号阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    system(cmd.data());
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);

    log();
    log("测试父进程 SIGCHLD => SIG_IGN");
    signal(SIGCHLD, SIG_IGN);
    log("阻塞所有信号");
    sigprocmask(SIG_SETMASK, &mask, NULL);
    for (int i = 1; i <= 5; ++i)
        if (fork() == 0) {
            log("第 " + std::to_string(i) + " 个子进程启动并退出");
            exit(-1);
        } else {
            sleep(1);
        }

    log("解除信号阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    system(cmd.data());
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);

    log();
    log("测试父进程 SIGCHLD => 捕获, 然后返回");
    signal(SIGCHLD, handle_signal_1);
    log("阻塞所有信号");
    sigprocmask(SIG_SETMASK, &mask, NULL);
    for (int i = 1; i <= 5; ++i)
        if (fork() == 0) {
            log("第 " + std::to_string(i) + " 个子进程启动并退出");
            exit(-1);
        } else {
            sleep(1);
        }

    log("解除信号阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    system(cmd.data());
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);

    log();
    log("测试父进程 SIGCHLD => 捕获, 调用 waitpid() 一次");
    signal(SIGCHLD, handle_signal_2);
    log("阻塞所有信号");
    sigprocmask(SIG_SETMASK, &mask, NULL);
    for (int i = 1; i <= 5; ++i)
        if (fork() == 0) {
            log("第 " + std::to_string(i) + " 个子进程启动并退出");
            exit(-1);
        } else {
            sleep(1);
        }

    log("解除信号阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    system(cmd.data());
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);

    log();
    log("测试父进程 SIGCHLD => 捕获, 调用 waitpid() 循环");
    signal(SIGCHLD, handle_signal_3);
    log("阻塞所有信号");
    sigprocmask(SIG_SETMASK, &mask, NULL);
    for (int i = 1; i <= 5; ++i)
        if (fork() == 0) {
            log("第 " + std::to_string(i) + " 个子进程启动并退出");
            exit(-1);
        } else {
            sleep(1);
        }

    log("解除信号阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    system(cmd.data());
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);

    log();
    log("测试父进程 SIGCHLD => 使用 SA_NOCLDWAIT 参数");
    set_signal();
    log("阻塞所有信号");
    sigprocmask(SIG_SETMASK, &mask, NULL);
    for (int i = 1; i <= 5; ++i)
        if (fork() == 0) {
            log("第 " + std::to_string(i) + " 个子进程启动并退出");
            exit(-1);
        } else {
            sleep(1);
        }

    log("解除信号阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    system(cmd.data());
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);
    waitpid(-1, NULL, WNOHANG);

    return 0;
}
