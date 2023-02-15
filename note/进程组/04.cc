
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
}

int main() {
    log("测试新建子进程对应的进程组(子进程调用exec之后)");
    log();

    pid_t child = fork();
    if (child == 0) {
        log("子进程调用exec");
        execl("/usr/bin/sleep", "sleep", "3", NULL);
        log("子进程失败");
        exit(-1);
    }
    sleep(1);
    log("新建子进程(" + std::to_string(child) + ")的进程组");
    test(child, child);
    kill(child, SIGKILL);

    sleep(1);
    log();
    log("主进程退出");

    return 0;
}
