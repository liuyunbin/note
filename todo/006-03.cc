
#include "log.h"

int main() {
    log();
    log("操作系统-会话-销毁: 会话不和终端绑定");
    log();

    if (fork() == 0) {
        log("建立新会话");
        test_sid();
        if (fork() == 0) {
            log("新会话的子进程");
            log("当前进程和父进程的信息");
            show_pid_pgid_sid(getpid());
            show_pid_pgid_sid(getppid());
            log("杀死父进程(会话首进程): " + std::to_string(getppid()));
            if (kill(getppid(), SIGKILL) < 0) {
                perror("");
            }
            sleep(1);
            log("当前进程和父进程的信息");
            show_pid_pgid_sid(getpid());
            show_pid_pgid_sid(getppid());
            exit(-1);
        } else {
            for (;;)
                ;
        }
    }

    sleep(3);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
