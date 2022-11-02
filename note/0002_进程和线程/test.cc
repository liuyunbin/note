#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <map>

std::map<int, std::string> m;

void handle_signal(int sig, siginfo_t* sig_info, void * ) {
    std::cout << getpid() << " 捕获信号 " << m[sig] << " 来自 " << sig_info->si_pid << std::endl;
    std::cout << getpid() << " 处理信号 " << m[sig] << " 中..." << std::endl;
    sleep(2);
    std::cout << getpid() << " 处理完成 " << m[sig] << std::endl;
}

void set_signal(bool block = false) {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    if (block) {
        sigfillset(&act.sa_mask);
    } else {
        sigemptyset(&act.sa_mask);
    }
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    for (auto key : m)
        sigaction(key.first, &act, NULL);
}

void send_signal(int sig, pid_t fd) {
    kill(fd, sig);
    //std::cout << getpid() << " 发送信号 " << m[sig] << std::endl;
}

void init() {
    m[SIGHUP   ] = " 1-SIGHUP";
    m[SIGINT   ] = " 2-SIGINT";
    m[SIGQUIT  ] = " 3-SIGQUIT";
    m[SIGILL   ] = " 4-SIGILL";
    m[SIGTRAP  ] = " 5-SIGTRAP";
    m[SIGABRT  ] = " 6-SIGABRT";
    m[SIGBUS   ] = " 7-SIGBUS";
    m[SIGFPE   ] = " 8-SIGFPE";
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
    m[SIGURG   ] = "23-SIGURG";
    m[SIGXCPU  ] = "24-SIGXCPU";
    m[SIGXFSZ  ] = "25-SIGXFSZ";
    m[SIGVTALRM] = "26-SIGVTAL";
    m[SIGPROF  ] = "27-SIGPROF";
    m[SIGWINCH ] = "28-SIGWINC";
    m[SIGIO    ] = "29-SIGIO";
    m[SIGPWR   ] = "30-SIGPWR";
    m[SIGSYS   ] = "31-SIGSYS";
}

int main() {
    init();

#if 0
    // 测试信号处理函数执行过程中, 相同的信号到达多个的情况
    pid_t fd = fork();

    if (fd == 0) {
        std::cout << "子进程: " << getpid() << std::endl;
        // 子进程
        set_signal();
        for (;;)
            ;
    } else {
        // 父进程
        sleep(2); // 保证子进程已设置信号处理
        std::cout << "父进程: " << getpid() << std::endl;
        send_signal(SIGUSR1, fd);
        sleep(1);
        for (int i = 1; i < 11; ++i) {
            send_signal(SIGUSR1, fd);
        }
        for (;;)
            ;
    }
#endif

#if 0
    // 测试信号处理函数执行过程中, 不同的信号到达多个的情况
    pid_t fd = fork();

    if (fd == 0) {
        std::cout << "子进程: " << getpid() << std::endl;
        // 子进程
        set_signal();
        for (;;)
            ;
    } else {
        // 父进程
        sleep(2); // 保证子进程已设置信号处理
        std::cout << "父进程: " << getpid() << std::endl;
        send_signal(SIGUSR1, fd);
        sleep(1);
        for (int i = 1; i < 11; ++i) {
            send_signal(SIGUSR2, fd);
        }
        for (;;)
            ;
    }
#endif

#if 1
    // 测试信号处理的顺序
    std::cout << "注册信号" << std::endl;
    set_signal(true);
    std::cout << "阻塞所有信号" << std::endl;
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    std::cout << "开始发送信号" << std::endl;
    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP)
            send_signal(key.first, getpid());
    std::cout << "发送信号完成" << std::endl;
    std::cout << "解除信号阻塞" << std::endl;
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    for (;;)
        ;
#endif
    return 0;
}

