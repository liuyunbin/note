
#include <errno.h>
#include <fcntl.h>
#include <pty.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd_log;

void log(const char* str, size_t len) {
    write(fd_log, str, len);
}

void log(const char* str) {
    log(str, strlen(str));
}

void run_tty(int argc, char* argv[]) {
    int tty;
    if (forkpty(&tty, NULL, NULL, NULL) == 0) {
        // tty 的进程
        execvp(argv[0], argv);
        log("exec 失败");
        exit(-1);
    }

    char buf[1024];
    for (;;) {
        int n = read(tty, buf, sizeof(buf));
        if (n <= 0)
            break;
        log(buf, n);
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fputs("use like: ./a.out ls\n", stdout);
        return -1;
    }

    // 初始化日志
    fd_log = open("/tmp/test.log", O_CREAT | O_WRONLY | O_APPEND);

    // 启动后台服务
    if (fork() > 0)
        return 0;
    if (fork() > 0)
        return 0;
    setsid();

    // 打印后台进程信息
    log("\n后台进程信息:\n");
    char buf[1024];
    snprintf(buf, sizeof(buf), "ps -p %d", getpid());
    FILE* fd = popen(buf, "r");
    while (fgets(buf, sizeof(buf), fd) != NULL)
        log(buf);
    pclose(fd);
    log("\n");

    // 执行命令
    run_tty(argc - 1, argv + 1);
    return 0;
}
