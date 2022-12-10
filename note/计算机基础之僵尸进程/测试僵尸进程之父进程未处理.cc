
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

int main() {
    log("测试僵尸进程之父进程未处理");
    log();

    pid_t child = fork();

    if (child == 0) {
        // 子进程
        log("子进程启动");
        for (;;)
            ;
    } else {
        // 父进程
        sleep(1);
        std::string cmd = "ps -o pid,comm,state -p ";
        cmd += std::to_string(child);
        log("子进程状态");
        system(cmd.data());
        log("杀死子进程 " + std::to_string(child));
        kill(child, SIGKILL);
        sleep(1);
        log("子进程状态");
        system(cmd.data());
    }

    return 0;
}
