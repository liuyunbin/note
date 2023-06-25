
#include "log.h"

void show(pid_t pid) {
    std::string msg;
    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);
}

void test() {
    log();
    show(getpid());

    std::string msg = "新建会话";
    if (setsid() < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    show(getpid());
    log();
}
