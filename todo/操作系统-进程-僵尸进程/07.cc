
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <string>

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

int main() {
    log();
    log("操作系统-僵尸进程-销毁: 杀死僵尸进程的父进程");
    log();

    if (fork() == 0) {
        pid_t fd = fork();

        if (fd == 0) {
            log("测试的子进程启动: " + std::to_string(getpid()));
            for (;;)
                ;
        } else if (fork() == 0) {
            log("测试的控制进程启动: " + std::to_string(getpid()));
            sleep(1);
            std::string cmd =
                "ps -o pid,ppid,comm,state -p " + std::to_string(fd);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的子进程: " + std::to_string(fd));
            kill(fd, SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的父进程: " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            return 0;
        } else {
            log("测试的父进程启动: " + std::to_string(getpid()));
            for (;;)
                ;
        }
    }

    sleep(4);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
