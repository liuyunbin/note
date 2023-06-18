

void handle_signal(int sig) { log("子进程捕捉到信号 SIGUSR1"); }

int main() {
    log();
    log("测试可被信号打断的休眠(指被捕获的信号)");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程启动");

        log("子进程注册信号处理函数");
        signal(SIGUSR1, handle_signal);

        log("子进程休眠10秒");
        sleep(10);
        log("子进程休眠完成");
        exit(-1);
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        wait(NULL);
    }

    log("主进程正常退出");
    log();

    return 0;
}
