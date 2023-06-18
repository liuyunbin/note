
#include "log.h"

void test(pid_t pid, pid_t pgid) {
    log();

    std::string msg;

    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);

    msg = "修改进程组 ";
    msg += std::to_string(getpgid(pid));
    msg += " => ";
    msg += std::to_string(pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    msg.clear();
    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);

    log();
}

int main() {
    log();
    log("测试修改进程组(原进程组和目标进程组属于不同会话)");
    log();

    pid_t child = fork();

    if (child == 0) {
        log("子进程创建新会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("子进程的状态信息");
    test(getpid(), child);
    sleep(1);
    log("主进程退出");
    log();

    return 0;
}
