

#include <string.h>
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

void show(pid_t pid) {
    std::string msg = "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);
}

void test(pid_t pid, pid_t pgid) {
    log();
    show(pid);

    std::string msg = "修改进程组 ";
    msg += std::to_string(getpgid(pid)) + " => " + std::to_string(pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    show(pid);
}

int main() {
    log();
    log("计算机操作系统-进程组: 新建子进程对应的进程组(子进程属于不同的会话)");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程新建会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("父进程会话: " + std::to_string(getsid(getpid())));
    log("子进程会话: " + std::to_string(getsid(fd)));
    log("新建子进程的进程组: " + std::to_string(fd));
    test(fd, fd);
    kill(fd, SIGKILL);

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
