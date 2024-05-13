
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
    log("计算机操作系统-孤儿进程");
    log();

    if (fork() == 0) {
        if (fork() == 0) {
            // 测试的子进程
            sleep(1);
            log("测试的子进程(" + std::to_string(getpid()) + ")启动");
            std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            cmd += std::to_string(getpid()) + "," + std::to_string(getppid());
            log("进程状态");
            system(cmd.data());
            log("杀死父进程(" + std::to_string(getppid()) + ")");
            kill(getppid(), SIGKILL);
            sleep(1);
            cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            cmd += std::to_string(getpid()) + "," + std::to_string(getppid());
            log("进程状态");
            system(cmd.data());
            return 0;
        } else {
            // 测试的父进程
            log("测试的父进程(" + std::to_string(getpid()) + ")启动");
            for (;;)
                ;
        }
    }

    sleep(3);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
