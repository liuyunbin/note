
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

std::string get_time() {
    time_t now = time(NULL);
    struct tm* info = localtime(&now);
    char buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", info);
    return buf;
}

void log(const std::string& msg = "") {
    std::cout << get_time() << " " << getpid() << " " << msg << std::endl;
}

void log(pid_t pid) {
    std::string msg = "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);
}

void test() {
    log(getpid());
    std::string msg = "新建会话";
    if (setsid() < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);
    log(getpid());
}

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
