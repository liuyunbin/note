
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
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
}

int main() {
    log();
    log("计算机操作系统-信号-阻塞");
    log();

    log("阻塞所有信号");
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    log("查看被阻塞的信号");
    sigset_t old_mask;
    sigprocmask(SIG_SETMASK, NULL, &old_mask);

    for (auto key : m)
        if (sigismember(&old_mask, key.first))
            log("已被阻塞的信号: " + m[key.first]);

    log("发送除 " + m[SIGKILL] + " 和 " + m[SIGSTOP] + " 外的所有信号");

    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP)
            kill(getpid(), key.first);

    log("查看待决的信号");
    sigset_t new_mask;
    sigpending(&new_mask);
    for (auto key : m)
        if (sigismember(&new_mask, key.first))
            log("待决的信号: " + m[key.first]);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
