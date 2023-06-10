
#include "log.h"

int main() {
    signal(SIGCHLD, SIG_IGN);

    log("测试销毁会话(会话不和终端绑定)");
    log();

    if (fork() == 0) {
        log("建立新会话");
        test();
        if (fork() == 0) {
            log("新会话的子进程");
            log("当前进程和父进程的信息");
            log(getpid());
            log(getppid());
            log("杀死父进程(会话首进程): " + std::to_string(getppid()));
            if (kill(getppid(), SIGKILL) < 0) {
                perror("");
            }
            sleep(1);
            log("当前进程和父进程的信息");
            log(getpid());
            log(getppid());
            exit(-1);
        } else {
            for (;;)
                ;
        }
    }

    sleep(3);
    log();
    log("主进程退出");

    return 0;
}
