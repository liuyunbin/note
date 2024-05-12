
#include "lshell.h"

std::map<std::string, int (*)(int argc, char* argv[])> m;  // 存储内置命令

// 内置命令
int do_about(int argc, char* argv[]) {
    printf("write by liuyunbin\n");
    return 0;
}

int do_exit(int argc, char* argv[]) {
    exit(0);
}

int do_cd(int argc, char* argv[]) {
    if (argc > 2) {
        printf("cd: too many arguments\n");
        return -1;
    }
    std::string user_home;

    uid_t user_id = getuid();

    struct passwd* pw_ptr = getpwuid(user_id);
    if (pw_ptr != NULL) {
        user_home = std::string(pw_ptr->pw_dir);
    }

    std::string str;
    if (argc == 1)
        str = user_home;
    else
        str = argv[1];

    if (chdir(str.data()) == -1) {
        perror("cd");
        return -1;
    }
    return 0;
}

#define LIMIT(name, X)                                                       \
    {                                                                        \
        struct rlimit rlim;                                                  \
        getrlimit(X, &rlim);                                                 \
        std::string s_cur;                                                   \
        if (rlim.rlim_cur == RLIM_INFINITY)                                  \
            s_cur = "unlimited";                                             \
        else                                                                 \
            s_cur = std::to_string(rlim.rlim_cur);                           \
        std::string s_max;                                                   \
        if (rlim.rlim_max == RLIM_INFINITY)                                  \
            s_max = "unlimited";                                             \
        else                                                                 \
            s_max = std::to_string(rlim.rlim_max);                           \
        printf("%20s %10s %10s %s\n", #X, s_cur.data(), s_max.data(), name); \
    }

int do_ulimit(int argc, char* argv[]) {
    LIMIT("虚拟内存大小", RLIMIT_AS);
    LIMIT("core 文件大小", RLIMIT_CORE);
    LIMIT("CPU 总的时间大小", RLIMIT_CPU);
    LIMIT("数据段(初始化数据, 未初始化数据, 堆)", RLIMIT_DATA);
    LIMIT("文件大小", RLIMIT_FSIZE);
    LIMIT("文件锁的个数", RLIMIT_LOCKS);
    LIMIT("内存中可以锁定的大小", RLIMIT_MEMLOCK);
    LIMIT("消息队列的大小", RLIMIT_MSGQUEUE);
    LIMIT("进程优先级的上限", RLIMIT_NICE);
    LIMIT("文件描述符的最大限制", RLIMIT_NOFILE);
    LIMIT("用户的进程线程数", RLIMIT_NPROC);
    LIMIT("物理内存大小", RLIMIT_RSS);
    LIMIT("调度的优先级", RLIMIT_RTPRIO);
    LIMIT("调度时 CPU 的最大耗时 毫秒", RLIMIT_RTTIME);
    LIMIT("信号队列的长度", RLIMIT_SIGPENDING);
    LIMIT("栈大小", RLIMIT_STACK);
    return 0;
}

void init_builtin() {
    m["about"]  = do_about;
    m["exit"]   = do_exit;
    m["cd"]     = do_cd;
    m["ulimit"] = do_ulimit;
    m["jobs"]   = do_jobs;
    m["bg"]     = do_bg;
    m["fg"]     = do_fg;
}

bool is_builtin(const cmd_t& cmd) {
    return m.find(cmd.vec[0]) != m.end();
}

bool run_builtin(int argc, char* argv[]) {
    return m[argv[0]](argc, argv);
}
