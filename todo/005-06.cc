
#include "log.h"

int main() {
    log();
    log("操作系统-进程组: 新建孙进程对应的进程组");
    log();

    int pipefd[2];
    pipe(pipefd);
    pid_t child = fork();
    if (child == 0) {
        pid_t grandchild = fork();

        if (grandchild == 0) {
            // 测试的孙进程
            close(pipefd[0]);
            close(pipefd[1]);
            for (;;)
                ;
        } else {
            // 测试的子进程
            close(pipefd[0]);
            std::string str = std::to_string(grandchild);
            write(pipefd[1], str.data(), str.size());
            close(pipefd[1]);
            for (;;)
                ;
        }
    } else {
        // 测试的父进程
        close(pipefd[1]);

        char        ch;
        std::string str;

        while (read(pipefd[0], &ch, 1) > 0) {
            str.push_back(ch);
        }
        pid_t grandchild = atoi(str.data());

        log("进程关系");
        std::string cmd = "ps -o pid,ppid,pgid,sid,comm -p";
        cmd += std::to_string(child) + ",";
        cmd += std::to_string(grandchild) + ",";
        cmd += std::to_string(getpid());
        system(cmd.data());
        log("修改孙进程的进程组: " + str);
        test_pgid(grandchild, grandchild);

        kill(child, SIGKILL);
        kill(grandchild, SIGKILL);
    }

    log();
    log("主进程正常退出");
    log();
    return 0;
}
