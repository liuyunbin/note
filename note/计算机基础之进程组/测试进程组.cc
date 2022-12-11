
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << ") ";
    std::cout << "进程组(" << getpgid(getpid()) << ") ";
    std::cout << "会话(" << getsid(getpid()) << "): " << msg << std::endl;
}

void log(pid_t pid) {
    std::string msg = "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);
}

void test(pid_t pid, pid_t pgid) {
    log(pid);
    std::string msg = "修改进程组 ";
    msg += std::to_string(getpgid(pid));
    msg += " => ";
    msg += std::to_string(pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);
    log(pid);
    log();
}

int main() {
    if (fork() == 0) {
        if (fork() == 0) {
            // 子进程
            log("测试进程组");
            log();

            pid_t child_1 = fork();
            if (child_1 == 0) {
                // 测试的第一个子进程
                for (;;)
                    ;
            } else {
                pid_t child_2 = fork();
                if (child_2 == 0) {
                    // 测试的第二个子进程
                    // 不在同一会话
                    setsid();
                    for (;;)
                        ;
                }

                int pipefd[2];
                pipe(pipefd);
                pid_t child_3 = fork();
                if (child_3 == 0) {
                    // 测试的第三个子进程
                    pid_t fd = fork();

                    if (fd == 0) {
                        // 测试的孙进程
                        close(pipefd[0]);
                        close(pipefd[1]);
                        for (;;)
                            ;
                    } else {
                        close(pipefd[0]);
                        std::string str = std::to_string(fd);
                        write(pipefd[1], str.data(), str.size());
                        close(pipefd[1]);
                        for (;;)
                            ;
                    }
                }
                close(pipefd[1]);

                char ch;
                std::string str;

                while (read(pipefd[0], &ch, 1) > 0) str.push_back(ch);
                pid_t grandchild = atoi(str.data());

                log("测试修改父进程的进程组");
                test(getppid(), getppid());
                log("测试修改自身进程的进程组");
                test(getpid(), getpid());
                log("测试修改在同一会话的子进程的进程组");
                test(child_1, child_1);
                log("测试修改在不同会话的子进程的进程组");
                test(child_2, child_2);
                log("测试目标进程组和原进程组不在同一会话");
                test(child_1, child_2);
                log("测试修改孙进程的进程组");
                test(grandchild, grandchild);

                log("测试修改会话ID的进程组");
                if (fork() == 0) {
                    setsid();
                    pid_t fd = fork();
                    if (fd == 0) {
                        setpgid(0, 0);
                        log(getpid());
                        for (;;)
                            ;
                    } else {
                        sleep(1);
                        test(getpid(), fd);
                        kill(fd, SIGKILL);
                        exit(-1);
                    }
                }
                sleep(2);

                kill(child_1, SIGKILL);
                kill(child_2, SIGKILL);
                kill(child_3, SIGKILL);
                kill(grandchild, SIGKILL);
                kill(getppid(), SIGKILL);
                exit(-1);
            }
        }
        // 测试的父进程
        for (;;)
            ;
    }
    sleep(3);
    log("主进程退出");

    return 0;
}
