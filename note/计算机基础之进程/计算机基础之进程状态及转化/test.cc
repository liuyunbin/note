
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

int main() {
    log("测试进程状态");

    pid_t fd = fork();
    std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);
    if (fd == 0) {
        if (fd == 0) {
            if (vfork() == 0) {
                sleep(2);
                exit(0);
            }
        }
        sleep(2);
        for (;;)
            ;
        exit(0);
    } else {
        sleep(1);
        log("运行 => 休眠(不可打断)");
        system(cmd.data());
        sleep(2);
        log("休眠(不可打断) => 休眠(可打断)");
        system(cmd.data());
        kill(fd, SIGTSTP);
        sleep(1);
        log("休眠 => 暂停");
        system(cmd.data());
        kill(fd, SIGCONT);
        sleep(1);
        log("暂停 => 运行");
        system(cmd.data());
        kill(fd, SIGKILL);
        sleep(1);
        log("运行 => 退出(僵尸)");
        system(cmd.data());
    }

    log();
    log("主进程正常退出");

    return 0;
}
