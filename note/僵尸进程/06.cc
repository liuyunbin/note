
#include <signal.h>
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

int main() {
    log("测试预防僵尸进程");
    log("测试杀死父进程");
    log();

    if (fork() == 0) {
        pid_t child = fork();
        std::string cmd = "ps -o pid,ppid,comm,state -p ";
        cmd += std::to_string(child);
        if (child == 0) {
            // 测试的子进程
            log("子进程启动");
            for (;;)
                ;
        } else if (fork() == 0) {
            // 测试的控制进程
            sleep(1);
            log("子进程状态");
            system(cmd.data());
            log("杀死父进程 " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            log("子进程状态");
            system(cmd.data());
            log("杀死子进程");
            kill(child, SIGKILL);
            sleep(1);
            log("子进程状态");
            system(cmd.data());
            exit(-1);
        } else {
            // 测试的父进程
            log("父进程启动");
            for (;;)
                ;
        }
    }

    sleep(4);

    log();
    log("主进程退出");

    return 0;
}
