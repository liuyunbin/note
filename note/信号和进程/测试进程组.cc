
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
    if (fork() == 0) {
        // 子进程
        log("测试孤儿进程组");
        log();

        pid_t child = fork();
        if (child == 0) {
            // 子进程
            for (;;)
                ;
        } else {
            std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            cmd += std::to_string(getpid()) + ",";
            cmd += std::to_string(getppid()) + ",";
            cmd += std::to_string(child);

            system(cmd.data());
            log("设置进程的进程组 " + std::to_string(getpid()));
            setpgid(getpid(), getpid());
            setpgid(child, child);
            setpgid(getppid(), getpid());
            system(cmd.data());
            kill(child, SIGKILL);
            exit(-1);
        }
    }
    sleep(3);
    log("主进程退出");

    return 0;
}
