
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
    log("产生僵尸进程, 不退出");
    log();
    pid_t child = fork();

    if (child == 0) {
        exit(0);
    }
    sleep(1);  // 保证子进程已启动并退出
    log("产生僵尸进程 " + std::to_string(child));
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(child);
    system(cmd.data());

    for (;;)
        ;

    return 0;
}
