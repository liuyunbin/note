

void test(pid_t pid, pid_t pgid) {
    log();

    std::string msg;

    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);

    msg = "修改进程组 ";
    msg += std::to_string(getpgid(pid));
    msg += " => ";
    msg += std::to_string(pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    msg.clear();
    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);

    log();
}

int main() {
    log();
    log("测试新建自身进程对应的进程组");
    log();

    test(getpid(), getpid());
    if (fork() == 0) {
        test(getpid(), getpid());
        exit(-1);
    }
    sleep(1);
    log("主进程退出");
    log();

    return 0;
}
