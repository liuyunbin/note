
#include <stdio.h>         // printf
#include <stdlib.h>        // exit
#include <string.h>        // strerror
#include <sys/resource.h>  // getrlimit setrlimit
#include <sys/time.h>      // getrlimit setrlimit
#include <unistd.h>        // chdir

#include "lshell.h"

int do_about(const cmd& cmd);
int do_exit(const cmd& cmd);
int do_quit(const cmd& cmd);
int do_cd(const cmd& cmd);
int do_ulimit(const cmd& cmd);
int do_jobs(const cmd& cmd);
int do_bg(const cmd& cmd);
int do_fg(const cmd& cmd);

// 内置命令
int do_about(cmd_t& cmd) {
    printf("write by liuyunbin\n");
    return 0;
}

int do_exit(cmd_t& cmd) {
    exit(EXIT_SUCCESS);
    return 0;
}

int do_quit(cmd_t& cmd) {
    exit(EXIT_SUCCESS);
    return 0;
}

int do_cd(cmd_t& cmd) {
    std::string str;

    if (cmd.cmd_vec.size() == 1) {
        str = get_user_home();
    } else if (cmd.cmd_vec.size() > 2) {
        printf("cd: too many arguments\n");
        return -1;
    } else {
        str = cmd.vec[1];
    }
    if (chdir(str.data()) == -1) {
        printf("cd %s : %s\n", str.data(), strerror(errno));
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

int do_ulimit(cmd_t& cmd) {
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

std::map<std::string, int (*)(cmd_t&)> m_builtin;

void init_cmd_builtin() {
    m_builtin["about"]  = do_about;
    m_builtin["exit"]   = do_exit;
    m_builtin["quit"]   = do_quit;
    m_builtin["cd"]     = do_cd;
    m_builtin["ulimit"] = do_ulimit;
    m_builtin["jobs"]   = do_jobs;
    m_builtin["bg"]     = do_bg;
    m_builtin["fg"]     = do_fg;
}

bool is_cmd_builtin(const cmd& cmd) {
    return m_builtin.find(cmd.str()) != m_builtin.end();
}

int run_cmd_builtin(const cmd& cmd) {
    if (is_cmd_builtin(cmd))
        return m_builtin[cmd.str](cmd);
    return -1;
}
