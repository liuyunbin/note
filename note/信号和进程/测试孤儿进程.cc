
#include <signal.h>
#include <stdlib.h>
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
    std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
    if (fork() == 0) {
        // 子进程
        log("测试孤儿进程");
        log();
        if (fork() == 0) {
            // 子进程
            std::string commond = cmd;
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            log("进程状态");
            system(commond.data());
            log("杀死父进程 " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            log("进程状态");
            commond = cmd;
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            return 0;
        } else {
            // 父进程
            for (;;)
                ;
            return 0;
        }
    }

    sleep(1);
    sleep(1);

    log("主进程退出");

    return 0;
}
