
#include "lshell.h"

void handle_signal(int sig) {
    for (;;) {
        int wstatus;
        int fd = waitpid(-1, &wstatus, WNOHANG | WUNTRACED | WCONTINUED);
        if (fd <= 0)
            break;
        update_jobs(fd, wstatus);
    }
}

void init_signal() {
    // 忽略键盘产生的信号
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    // 子进程状态变化时, 父进程更新状态
    signal(SIGCHLD, handle_signal);
}
