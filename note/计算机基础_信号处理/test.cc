
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

jmp_buf buf;

void handle_signal(int sig, siginfo_t* sig_info, void * ) {
    log("信号处理函数捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
    // 对 SIGUSR1 SIGUSR2 特殊处理
    if (sig == SIGUSR1 || sig == SIGUSR2) {
        log("信号处理函数处理来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig] + " 中...");
        sleep(1);
        log("信号处理函数处理来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig] + " 完成");
    }
    // 保证 SIGABRT SIGSEGV SIGFPE 不退出
    if (sig == SIGABRT || sig == SIGSEGV || sig == SIGFPE) {
        longjmp(buf, 1);
    }
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

int main() {
    log("主函数初始化");
    init();

    log("主函数注册信号处理");
    set_signal();

    log();
    if (setjmp(buf) == 0) {
        log("主函数调用 abort()");
        abort();
    }

    log();
    if (setjmp(buf) == 0) {
        log("主函数测试空指针异常");
        int* p = NULL;
        *p = 10;
    }

    log();
    if (setjmp(buf) == 0) {
        log("主函数测试浮点数异常");
        int a = 1/0;
    }

    log();
    log("主函数测试信号处理函数执行过程中, 相同的信号到达多个");
    pid_t fd = fork();

    if (fd == 0) {
        // 子进程
        sleep(5);
        return 0;
    } else {
        // 父进程
        log("父进程发送信号 " + m[SIGUSR1]);
        kill(fd, SIGUSR1);
        sleep(1);
        for (int i = 1; i < 5; ++i) {
            log("父进程发送信号 " + m[SIGUSR1]);
            kill(fd, SIGUSR1);
        }
    }
    sleep(10);
#if 0
    // 测试信号处理的顺序
    std::cout << "注册信号" << std::endl;
    set_signal(true);
    std::cout << "阻塞所有信号" << std::endl;
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    std::cout << "开始发送信号" << std::endl;
    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP && key.first != SIGUSR1 && key.first != SIGUSR2)
            kill(getpid(), key.first);
    std::cout << "发送信号完成" << std::endl;
    std::cout << "解除信号阻塞" << std::endl;
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    for (;;)
        ;
#endif





    log("主函数退出");

    return 0;
}


#if 0
    // 测试信号处理函数执行过程中, 不同的信号到达多个的情况
    // 结论: 信号处理过程中, 不同信号到来会直接处理, 多个不同信号后续只处理一个, 多余的会丢弃
    //       处理完成以后, 再处理之前的信号
    pid_t fd = fork();

    if (fd == 0) {
        // 子进程
        set_signal();
        std::cout << getpid() << " 设置信号处理函数完成" << std::endl;
        for (;;)
            ;
    } else {
        // 父进程
        sleep(2); // 保证子进程已设置信号处理
        std::cout << getpid() << " 发送信号 " << m[SIGUSR1] << std::endl;
        kill(fd, SIGUSR1);
        sleep(1);
        for (int i = 1; i < 5; ++i) {
            std::cout << getpid() << " 发送信号 " << m[SIGUSR2] << std::endl;
            kill(fd, SIGUSR2);
        }
        for (;;)
            ;
    }
#endif

#if 0
    // 测试信号处理的顺序
    std::cout << "注册信号" << std::endl;
    set_signal(true);
    std::cout << "阻塞所有信号" << std::endl;
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    std::cout << "开始发送信号" << std::endl;
    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP && key.first != SIGUSR1 && key.first != SIGUSR2)
            kill(getpid(), key.first);
    std::cout << "发送信号完成" << std::endl;
    std::cout << "解除信号阻塞" << std::endl;
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    for (;;)
        ;
#endif

#if 0
    // 测试僵尸进程
    pid_t fd = fork();

    if (fd == 0) {
        // 子进程
        std::cout << getpid() << " 子进程退出" << std::endl;
    } else {
        // 父进程
        for (;;)
            ;
    }
#endif

#if 0
    set_signal();
    std::cout << "父进程: " << getppid() << std::endl;
    std::cout << "  进程: " << getpid()  << std::endl;
    for (;;)
        ;
#endif

