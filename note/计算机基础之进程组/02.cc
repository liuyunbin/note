
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

void log(pid_t pid) {
    std::string msg = "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);
}

void test(pid_t pid, pid_t pgid) {
    log(pid);
    std::string msg = "修改进程组 ";
    msg += std::to_string(getpgid(pid));
    msg += " => ";
    msg += std::to_string(pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);
    log(pid);
    log();
}

int main() {
    log("测试新建父进程对应的进程组");
    log();

    if (fork() == 0) {
        // 测试的父进程
        if (fork() == 0) {
            // 测试的子进程
            log("新建父进程(" + std::to_string(getppid()) + ") 的进程组");
            test(getppid(), getppid());
            kill(getppid(), SIGKILL);
            exit(-1);
        }
        for (;;)
            ;
    }
    sleep(2);
    log("主进程退出");

    return 0;
}
