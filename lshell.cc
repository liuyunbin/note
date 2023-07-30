
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

enum status_t {
    FG_RUN,   // 前台运行
    BG_RUN,   // 后台运行
    FG_STOP,  // 前台暂停
    BG_STOP,  // 后台暂停
    QUIT      // 退出
};

struct job_t {
    pid_t            pgid;        // 进程组 ID
    status_t         status;      // 作业状态
    int              count_bg;    // 进程数 -- 后台运行
    int              count_fg;    // 进程数 -- 前台运行
    int              count_st;    // 进程数 -- 暂停
    int              count_quit;  // 进程数 -- 退出
    vector<pid_t>    pids;        // 任务的进程 ID
    vector<string>   cmds;        // 任务的字符串
    vector<status_t> sts;         // 任务的状态
};

queue<int>      jids;  // 待用的作业号
map<int, job_t> jobs;  // 作业
map<pid_t, int> pids;  // 进程号 -> 作业号

uid_t  user_id;
string user_name;
string user_home;

map<string, void (*)()> m;

struct cmd_t {
    vector<string> cmd_vec;
    string         cmd_str;
    string         in;
    string         out;
    string         add;
};

// 获取命令行提示符
string get_prompt() {
    char  *p        = get_current_dir_name();
    string curr_dir = p;
    free(p);

    string prompt = user_name + ":";
    if (curr_dir == user_home) {
        prompt += "~";
    } else if (curr_dir < user_home) {
        prompt += curr_dir;
    } else if (curr_dir.compare(0, user_home.size(), user_home) != 0) {
        prompt += curr_dir;
    } else if (curr_dir[user_home.size()] != '/') {
        prompt += curr_dir;
    } else {
        prompt += '~';
        prompt += curr_dir.data() + user_home.size();
    }

    if (user_id == 0)
        prompt += "# ";
    else
        prompt += "$ ";

    return prompt;
}

// 获取用户的输入
// 处理掉 ~ 代表目录的位置
int get_cmd(const string &prompt, string &cmd) {
    // 读取一行，不包括 '\n'
    char *p = readline(prompt.data());
    if (p == NULL)
        return -1;  // 读入 EOF

    cmd.clear();
    for (size_t i = 0; p[i] != '\0'; ++i) {
        if (p[i] != '~')
            cmd += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            cmd += user_home;
        else
            cmd += p[i];
    }

    free(p);  // 释放资源，避免内存泄漏

    return 0;
}

// 解析单个命令
int parse_cmd(const string &str, vector<cmd_t> &cmds) {
    cmd_t  cmd;
    size_t i = 0;
    for (;;) {
        while (i < str.size() && str[i] == ' ')
            ++i;
        if (i == str.size())
            return 0;
        if (str[i] == '<') {
            while (i < str.size() && str[i] == ' ')
                ++i;
            if (i == str.size()) {
                printf("Please use: cmd < file_name\n");
                return -1;
            }
            string name;
            while (i < str.size() && str[i] != ' ')
                name.push_back(str[i++]);
            cmd.in = name;
            continue;
        }
        if (str[i] == '>') {
            bool add = false;
            if (i + 1 < str.size() && str[i + 1] == '>') {
                ++i;
                add = true;
            }

            while (i < str.size() && str[i] == ' ')
                ++i;
            if (i == str.size()) {
                if (add)
                    printf("Please use: cmd << file_name\n");
                else
                    printf("Please use: cmd <  file_name\n");
                return -1;
            }
            string name;
            while (i < str.size() && str[i] != ' ')
                name.push_back(str[i++]);
            if (add)
                cmd.add = name;
            else
                cmd.out = name;
            continue;
        }
        string name;
        while (i < str.size() && str[i] != ' ')
            name.push_back(str[i++]);
        cmd.cmd_vec.push_back(name);
    }
    cmd.cmd_str = str;
    cmds.push_back(cmd);
}

// 解析用户的输入
int parse_input(string &input, vector<cmd_t> &cmds, status_t &st) {
    // 去掉末尾的空白
    while (!input.empty() && input.back() == ' ')
        input.pop_back();
    // 加入历史命令
    if (!input.empty())
        add_history(input.data());
    // 判断是否后台运行
    if (!input.empty() && input.back() == '&') {
        input.pop_back();
        st = BG;
    } else {
        st = FG;
    }
    // 处理管道并存储其参数
    cmds.clear();
    size_t i = 0;
    for (;;) {
        while (i < input.size() && input[i] == ' ')
            ++i;
        if (i == input.size())
            break;
        if (cmd[i] == '|') {
            printf("invalid command!\n");
            return -1;
        }
        string str;
        while (i < input.size() && input[i] != '|')
            str.push_back(input[i]);
        int ret = parse_cmd(str, cmds);  // 解析每一个命令
        if (ret != 0)
            return ret;
        if (i < input.size())
            ++i;
    }
    return 0;
}

int do_about(cmd_t &cmd) {
    printf("write by liuyunbin\n");
    return 0;
}

int do_exit(cmd_t &cmd) {
    exit(EXIT_SUCCESS);
    return 0;
}

int do_quit(cmd_t &cmd) {
    exit(EXIT_SUCCESS);
    return 0;
}

int do_cd(cmd_t &cmd) {
    const char *p;

    if (cmd.cmd_vec.size() == 1) {
        p = user_home.data();
    } else if (cmd.cmd_vec.size() > 2) {
        printf("cd: too many arguments\n");
        return;
    } else {
        p = cmd.cmd_vec[1].data();
    }
    if (chdir(p) == -1) {
        printf("cd %s : %s\n", p, strerror(errno));
        return -1;
    }
    return 0;
}

#define LIMIT(name, X)                                                       \
    {                                                                        \
        struct rlimit rlim;                                                  \
        getrlimit(X, &rlim);                                                 \
        string s_cur;                                                        \
        if (rlim.rlim_cur == RLIM_INFINITY)                                  \
            s_cur = "unlimited";                                             \
        else                                                                 \
            s_cur = to_string(rlim.rlim_cur);                                \
        string s_max;                                                        \
        if (rlim.rlim_max == RLIM_INFINITY)                                  \
            s_max = "unlimited";                                             \
        else                                                                 \
            s_max = to_string(rlim.rlim_max);                                \
        printf("%20s %10s %10s %s\n", #X, s_cur.data(), s_max.data(), name); \
    }

int do_ulimit(cmd_t &cmd) {
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
}

// 处理重定向
int handle_redirection(const string &filename, int flag, int fd_new) {
    if (filename.empty())
        return 0;
    int fd = open(filename.data(), flag, 0644);
    if (fd < 0) {
        printf("can't open %s for: %s\n", filename.data(), strerror(errno));
        return -1;
    }
    dup2(fd, fd_new);
    close(fd);
    return 0;
}

int handle_redirection(const cmd_t &cmd) {
    int ret;
    // 输入重定向
    ret = handle_redirection(cmd.in, O_RDONLY, STDIN_FILENO);
    if (ret != 0)
        return ret;
    // 输出重定向
    ret = handle_redirection(cmd.out, O_WRONLY | O_CREAT, STDOUT_FILENO);
    if (ret != 0)
        return ret;
    // 添加重定向
    ret = handle_redirection(
        cmd.add, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
    if (ret != 0)
        return ret;
    return 0;
}

int run_cmd(const cmd_t &cmd) {
    // 处理重定向
    int ret = handle_redirection(cmd);
    if (ret != 0)
        return ret;
    // 处理内置命令
    if (m.find(cmd.cmd[0]) != m.end())
        return m[argv[0]](cmd);
    // 处理非内置命令
    char **argv;
    argv = (char **)malloc(sizeof(cmd.cmd.size()) + 1);
    for (size_t i = 0; i < cmd.cmd.size(); ++i)
        argv[i] = cmd.cmd[i].data();
    argv[cmd.size()] = NULL;
    execvp(argv[0], argv);
    perror(argv[0]);
    free(argv);
    return -1;
}

void handle_signal(int sig) {
    for (;;) {
        int wstatus;
        int fd = waitpid(-1, &wstatus, WNOHANG | WUNTRACED);
        if (fd <= 0)
            break;

        if (WIFSTOPPED(wstatus)) {
            // 子进程暂停
        } else {
            // 子进程退出
        }

        WSTOPSIG(wstatus)
    }
    while (jobs.find(jid) != jobs.end() && jobs[jid].st == BG &&
           jobs[jid].counts != 0)
}

int run_cmd(vector<cmd_t> &cmds, status_t st) {
    if (cmds.empty()) {
        // 命令为空, 直接跳过
        return 0;
    }
    // 检测命令是否为空
    for (size_t i = 0; i < cmds.size(); ++i)
        if (cmds[i].cmd_vec.empty()) {
            printf("commond is empty: %s\n", cmds[i].cmd_str.data());
            return -1;
        }

    // 是否在当前进程处理
    if (st == BG && cmds.size() == 1 && cmds[0].empty() &&
        cmds[0].out.empty() && cmds[0].add.empty()) {
        // 非 管道 重定向 以及 后台命令, 才可能在当前进程中运行
        if (m.find(cmds[0].cmd_vec[0]) != m.end())
            return m[argv[0]](cmds[0]);
    }

    sigset_t mask_all;
    sigset_t mask_empty;
    sigfillset(&mask_all);
    sigemptyset(&mask_empty);

    sigprocmask(SIG_SETMASK, &mask_all, NULL);  // 阻塞所有信号

    if (jids.empty()) {
        printf("to many jobs\n");
        sigprocmask(SIG_UNBLOCK, &mask_all, NULL);  // 解除信号阻塞
        return -1;
    }
    int jid = jids.front();
    jids.pop();

    job_t job;
    for (size_t i = 0; i < cmds.size(); ++i) {
        int pipe_fd[2];
        if (i + 1 != cmds.size() && pipe(pipe_fd) < 0) {
            // 不是最后一个命令需要新建管道
            perror("");
            return -1;
        }
        pid_t fd = fork();

        if (fd == 0) {
            // 子进程
            setpgid(0, i == 0 ? 0 : job.pgid);  // 设置新的进程组

            // 恢复信号处理
            signal(SIGINT, SIG_DFL);   // ctrl+c
            signal(SIGQUIT, SIG_DFL);  // ctrl+/
            signal(SIGTSTP, SIG_DFL);  // ctrl+z
            signal(SIGCHLD, SIG_DFL);  // 子进程退出, 暂停, 继续
            sigprocmask(SIG_UNBLOCK, &mask_all, NULL);  // 解除信号阻塞
            if (i + 1 != cmds.size()) {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);  // 将标准输出重定向到管道
                close(pipe_fd[1]);
            }
            return run_cmd(cmd);
        } else {
            // 父进程
            // 添加作业
            if (i == 0) {
                job.pgid   = fd;
                job.status = st;
                job.counts = 0;
            }
            job.pids.push_back(fd);
            job.cmds.push_back(cmds[i].cmd_str);
            job.sts.push_back(RUN);
            pids[fd] = jjid;

            setpgid(0, job.pgid);  // 设置新的进程组

            if (i + 1 != cmds.size()) {
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);  // 将标准输入重定向到管道
                close(pipe_fd[1]);
            }
        }
    }

    jobs.push_back(job);
    jobs[jid] = job;

    if (st == BG) {
        // 前台作业
        tcsetpgrp(0, job.pgid);  // 设置前台进程组
        while (tcgetpgrp(0) == job.pgid)
            sigsuspend(&mask_empty);  // 解阻塞所有信号, 然后暂停
    }
    sigprocmask(SIG_UNBLOCK, &mask_all, NULL);  // 解除信号阻塞
}

void init() {
    // 设置信号处理
    signal(SIGINT, SIG_IGN);         // ctrl+c
    signal(SIGQUIT, SIG_IGN);        // ctrl+/
    signal(SIGTSTP, SIG_IGN);        // ctrl+z
    signal(SIGTTIN, SIG_IGN);        // 后台读
    signal(SIGTTOU, SIG_IGN);        // 后台写
    signal(SIGCHLD, handle_signal);  // 子进程退出, 暂停, 继续

    // 初始化作业号
    for (int i = 1; i <= JOB_MAX; ++i) {
        jjids.push(i);
    }

    // 初始化内置命令
    m["about"]  = do_about;
    m["exit"]   = do_exit;
    m["quit"]   = do_quit;
    m["cd"]     = do_cd;
    m["ulimit"] = do_ulimit;

    // 初始化用户信息
    user_id            = getuid();
    struct passwd *pwd = getpwuid(user_id);

    user_name = pwd->pw_name;
    user_home = pwd->pw_dir;
}

int main() {
    init();

    for (;;) {
        // 获取提示符
        string prompt = get_prompt();
        // 获取命令行
        string   cmd;
        status_t st;
        if (get_cmd(prompt, cmd, st) == -1)
            return -1;  // 读到 EOF, 退出
        // 以管道为分割符解析命令行
        vector<cmd_t> cmds;
        if (parse_line(cmd, cmds) == -1)
            continue;  // 命令不合法, 直接跳过
        run_cmd(cmds, st);
        tcsetpgrp(0, getpid());  // 设置前台进程组
    }

    return 0;
}
