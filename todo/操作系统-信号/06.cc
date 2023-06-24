

#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

std::map<int, std::string> m{
    {SIGHUP,    " 1-SIGHUP"   },
    {SIGINT,    " 2-SIGINT"   },
    {SIGQUIT,   " 3-SIGQUIT"  },
    {SIGILL,    " 4-SIGILL"   },
    {SIGTRAP,   " 5-SIGTRAP"  },
    {SIGABRT,   " 6-SIGABRT"  },
    {SIGBUS,    " 7-SIGBUS"   },
    {SIGFPE,    " 8-SIGFPE"   },
    {SIGKILL,   " 9-SIGKILL"  },
    {SIGUSR1,   "10-SIGUSR1"  },
    {SIGSEGV,   "11-SIGSEGV"  },
    {SIGUSR2,   "12-SIGUSR2"  },
    {SIGPIPE,   "13-SIGPIPE"  },
    {SIGALRM,   "14-SIGALRM"  },
    {SIGTERM,   "15-SIGTERM"  },
    {SIGSTKFLT, "16-SIGSTKFLT"},
    {SIGCHLD,   "17-SIGCHLD"  },
    {SIGCONT,   "18-SIGCONT"  },
    {SIGSTOP,   "19-SIGSTOP"  },
    {SIGTSTP,   "20-SIGTSTP"  },
    {SIGTTIN,   "21-SIGTTIN"  },
    {SIGTTOU,   "22-SIGTTOU"  },
    {SIGURG,    "23-SIGURG"   },
    {SIGXCPU,   "24-SIGXCPU"  },
    {SIGXFSZ,   "25-SIGXFSZ"  },
    {SIGVTALRM, "26-SIGVTALRM"},
    {SIGPROF,   "27-SIGPROF"  },
    {SIGWINCH,  "28-SIGWINCH" },
    {SIGIO,     "29-SIGIO"    },
    {SIGPWR,    "30-SIGPWR"   },
    {SIGSYS,    "31-SIGSYS"   }
};

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 " + m[sig]);
    log("处理信号 " + m[sig] + " 中...");
    sleep(2);
    log("处理信号 " + m[sig] + " 完成");
}

int main() {
    log();
    log("操作系统-信号: 信号处理过程中不同的信号到达");
    log();

    log("设置信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程启动");
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 " + m[SIGUSR1]);
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 " + m[SIGUSR2]);
        kill(fd, SIGUSR2);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log();
    log("主进程正常退出");
    log();
    return 0;
}
