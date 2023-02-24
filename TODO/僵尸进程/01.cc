
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
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
    log("测试僵尸进程");
    log("测试父进程未处理子进程退出的状态信息");
    log();

    pid_t child = fork();

    if (child == 0) {
        // 子进程
        log("子进程已启动");
        for (;;)
            ;
    }
    sleep(1);  // 保证子进程已启动
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(child);
    log("子进程状态");
    system(cmd.data());
    log("杀死子进程 " + std::to_string(child));
    kill(child, SIGKILL);
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log();
    log("主进程退出");

    return 0;
}
