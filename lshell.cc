
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
#include <string>
#include <vector>

// 用户信息
uid_t       user_id;    // 用户 ID
std::string user_name;  // 用户名称
std::string user_home;  // 用户主目录

void init_user_info() {
    user_id            = getuid();
    struct passwd *pwd = getpwuid(user_id);
    user_name          = pwd->pw_name;
    user_home          = pwd->pw_dir;
}

// 获取命令行提示符
std::string prompt;

void get_prompt() {
    char       *p        = get_current_dir_name();
    std::string curr_dir = p;
    free(p);

    prompt = user_name + ":";
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
}

// 获取用户的输入, 处理掉 ~ 代表目录的位置
std::string input;

void get_input() {
    // 读取一行，不包括 '\n'
    char *p = readline(prompt.data());
    if (p == NULL) {
        // printf("read EOF, exit\n");
        exit(0);
    }
    input.clear();
    for (size_t i = 0; p[i] != '\0' && p[i] != '\n'; ++i)
        if (p[i] != '~')
            input += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            input += user_home;
        else
            input += p[i];
    free(p);
}

// 命令

struct cmd_t {
    std::vector<std::string> cmd_vec;
    std::string              cmd_str;
    std::string              in;
    std::string              out;
    std::string              add;
};

std::vector<cmd_t> cmds;
bool               fg;  // 此轮作业是否是前台作业

// 解析单个命令
int parse_cmd(std::string str) {
    while (!str.empty() && str.back() == ' ')
        str.pop_back();
    cmd_t cmd;
    cmd.cmd_str = str;
    size_t i    = 0;
    for (;;) {
        while (i < str.size() && str[i] == ' ')
            ++i;
        if (i == str.size())
            break;
        if (str[i] == '<') {
            while (++i < str.size() && str[i] == ' ')
                ;
            if (cmd.cmd_vec.empty() || i == str.size()) {
                printf("please use: cmd <  file_name\n");
                return -1;
            }
            std::string name;
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
            while (++i < str.size() && str[i] == ' ')
                ;
            if (cmd.cmd_vec.empty() || i == str.size()) {
                if (add)
                    printf("please use: cmd >> file_name\n");
                else
                    printf("please use: cmd >  file_name\n");
                return -1;
            }
            std::string name;
            while (i < str.size() && str[i] != ' ')
                name.push_back(str[i++]);
            if (add)
                cmd.add = name;
            else
                cmd.out = name;
            continue;
        }
        std::string name;
        while (i < str.size() && str[i] != ' ')
            name.push_back(str[i++]);
        cmd.cmd_vec.push_back(name);
    }
    cmds.push_back(cmd);
    return 0;
}

// 解析用户的输入
void parse_input() {
    // 去掉末尾的空白
    while (!input.empty() && input.back() == ' ')
        input.pop_back();
    // 加入历史命令
    if (!input.empty())
        add_history(input.data());
    // 判断是否后台运行
    if (!input.empty() && input.back() == '&') {
        input.pop_back();
        fg = false;
    } else {
        fg = true;
    }
    // 处理管道并存储其参数
    cmds.clear();
    size_t i = 0;
    for (;;) {
        while (i < input.size() && input[i] == ' ')
            ++i;
        if (i == input.size())
            break;
        if (input[i] == '|') {
            printf("invalid cmd!\n");
            cmds.clear();
            return;
        }
        std::string str;
        while (i < input.size() && input[i] != '|')
            str.push_back(input[i++]);
        if (parse_cmd(str) != 0) {  // 解析每一个命令
            cmds.clear();
            return;
        }
        if (i < input.size())
            ++i;
    }
}

// 处理重定向
int handle_redirection(const std::string &filename, int flag, int fd_new) {
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
    // 输入重定向
    if (handle_redirection(cmd.in, O_RDONLY, STDIN_FILENO) != 0)
        return -1;
    // 输出重定向
    if (handle_redirection(
            cmd.out, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO) != 0)
        return -1;
    // 添加重定向
    if (handle_redirection(
            cmd.add, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO) != 0)
        return -1;
    return 0;
}

// 作业
enum status_t {
    RUN,   // 运行
    STOP,  // 暂停
    KILL,  // 被杀死
    DONE   // 完成
};

struct task_t {
    std::string cmd;     // 进程命令
    status_t    status;  // 进程状态
};

struct job_t {
    pid_t                   pgid;        // 进程组 ID
    int                     count_run;   // 进程数 -- 运行
    int                     count_stop;  // 进程数 -- 暂停
    int                     count_kill;  // 进程数 -- 被杀死
    int                     count_done;  // 进程数 -- 退出
    std::map<pid_t, task_t> tasks;       // 任务的进程信息
};

std::map<int, job_t> jobs;          // 作业
std::map<pid_t, int> pids;          // 进程号 -> 作业号
int                  next_jid = 1;  // 下一个可用的作业号
int                  curr_jid;      // 当前的作业号

sigset_t mask_child;
sigset_t mask_empty;

void init_job() {
    sigaddset(&mask_child, SIGCHLD);
    sigemptyset(&mask_empty);
}

// 调用此函数前需要阻塞 SIGCHLD
// 此时, 主进程一定是前台进程组
int list_job(int jid, bool no_status = false) {
    if (jid == -1) {
        for (auto &it : jobs)
            list_job(it.first);
        return 0;
    }
    if (jobs.find(jid) == jobs.end()) {
        printf("can't find job %d\n", jid);
        return -1;
    }
    bool first = true;
    for (auto it : jobs[jid].tasks) {
        const char *p;
        if (no_status)
            p = "";
        else if (it.second.status == RUN)
            p = "run ";
        else if (it.second.status == STOP)
            p = "stop";
        else if (it.second.status == KILL)
            p = "killed";
        else
            p = "done";
        const char *cmd = no_status ? "" : it.second.cmd.data();
        if (first) {
            first = false;
            printf("[%d] %d %s %s\n", jid, it.first, p, cmd);
        } else {
            printf("[%c] %d %s %s\n", ' ', it.first, p, cmd);
        }
    }
    return 0;
}

// 检测并删除已经完成的作业, 此时主进程一定是前台进程组
void check_job() {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    for (auto it = jobs.begin(); it != jobs.end();) {
        if (it->second.count_run != 0 || it->second.count_stop != 0) {
            // 当前作业还没做完
            ++it;
            continue;
        }
        // 当前作业已经做完
        if (it->first != curr_jid)
            list_job(it->first);
        // 删除进程号到作业号的映射
        for (auto &v : it->second.tasks)
            pids.erase(v.first);
        // 删除此作业
        it = jobs.erase(it);
        // 修正下一个可以使用的作业号
        next_jid = 0;
        for (auto &v : jobs)
            next_jid = std::max(v.first, next_jid);
        ++next_jid;
    }
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
}

// 内置命令
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
        return 0;
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
    return 0;
}

// do_ls
std::string uid_to_name(uid_t uid) {
    struct passwd *pw_ptr = getpwuid(uid);

    if (pw_ptr == NULL) {  // 无该 uid 对应的用户
        return std::to_string(uid);
    } else {
        return std::string(pw_ptr->pw_name);
    }
}

std::string gid_to_name(gid_t gid) {
    struct group *grp_ptr = getgrgid(gid);

    if (grp_ptr == NULL) {  // 无该 gid 对应的组
        return std::to_string(gid);
    } else {
        return std::string(grp_ptr->gr_name);
    }
}

void mode_to_letters(int mode, char *str) {
    strcpy(str, "----------");

    // 文件类型
    if (S_ISDIR(mode))
        str[0] = 'd';  // 目录
    if (S_ISCHR(mode))
        str[0] = 'c';  // 设备文件
    if (S_ISBLK(mode))
        str[0] = 'b';  // 块文件

    // 用户权限
    if (mode & S_IRUSR)
        str[1] = 'r';
    if (mode & S_IWUSR)
        str[2] = 'w';
    if (mode & S_IXUSR)
        str[3] = 'x';

    // 组权限
    if (mode & S_IRGRP)
        str[4] = 'r';
    if (mode & S_IWGRP)
        str[5] = 'w';
    if (mode & S_IXGRP)
        str[6] = 'x';

    // 其他人权限
    if (mode & S_IROTH)
        str[7] = 'r';
    if (mode & S_IWOTH)
        str[8] = 'w';
    if (mode & S_IXOTH)
        str[9] = 'x';
}

void show_file_info(const char *file_name, const struct stat *stat_ptr) {
    char mode_str[11];
    mode_to_letters(stat_ptr->st_mode, mode_str);

    printf("%s", mode_str);
    printf("%4d ", (int)stat_ptr->st_nlink);
    printf("%-8s ", uid_to_name(stat_ptr->st_uid).data());
    printf("%-8s ", gid_to_name(stat_ptr->st_gid).data());
    printf("%8ld ", (long)stat_ptr->st_size);
    printf("%.12s ", 4 + ctime(&stat_ptr->st_mtime));
    printf("%s\n", file_name);
}

int do_stat(const char *file_name, int dir_fd) {
    struct stat info;

    if (fstatat(dir_fd, file_name, &info, 0) == -1) {
        perror(file_name);
        return -1;
    }
    show_file_info(file_name, &info);
    return 0;
}

int is_directory(const char *name) {
    struct stat info;
    if (stat(name, &info) == -1) {
        perror(name);
        return -1;
    }
    return S_ISDIR(info.st_mode) ? 0 : 1;
}

int do_ls(cmd_t &cmd) {
    const char *name;
    if (cmd.cmd_vec.size() == 1)
        name = ".";
    else
        name = cmd.cmd_vec[1].data();
    int ret = is_directory(name);
    if (ret == -1)
        return -1;
    if (ret == 0) {  // 目录
        DIR *dir_ptr = opendir(name);
        if (dir_ptr == NULL) {  // 无法打开目录
            perror(name);
            return -1;
        }
        struct dirent *dirent_ptr;
        while ((dirent_ptr = readdir(dir_ptr)) != NULL)
            if (do_stat(dirent_ptr->d_name, dirfd(dir_ptr)) == -1)
                return -1;
        closedir(dir_ptr);
        return 0;
    } else {  // 普通文件
        return do_stat(name, AT_FDCWD);
    }
}

int do_jobs(cmd_t &cmd) {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    list_job(-1);
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

int do_bg(cmd_t &cmd) {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    if (cmd.cmd_vec.size() != 2) {
        printf("please use bg jid\n");
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    int jid = atoi(cmd.cmd_vec[1].data());
    if (jobs.find(jid) == jobs.end()) {
        printf("job not find: %d\n", jid);
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    kill(-jobs[jid].pgid, SIGCONT);
    list_job(jid);                                // 可能状态还没更新
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

int do_fg(cmd_t &cmd) {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    if (cmd.cmd_vec.size() != 2) {
        printf("please use fg jid\n");
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    int jid = atoi(cmd.cmd_vec[1].data());
    if (jobs.find(jid) == jobs.end()) {
        printf("job not find: %d\n", jid);
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    tcsetpgrp(0, jobs[jid].pgid);
    kill(-jobs[jid].pgid, SIGCONT);
    curr_jid = jid;  // 为了避免作业控制打出前台任务
    while (tcgetpgrp(0) == jobs[jid].pgid)
        sigsuspend(&mask_empty);  // 解阻塞信号, 然后暂停
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

std::map<std::string, int (*)(cmd_t &)> m;

void init_cmd_builtin() {
    m["about"]  = do_about;
    m["exit"]   = do_exit;
    m["quit"]   = do_quit;
    m["cd"]     = do_cd;
    m["ulimit"] = do_ulimit;
    m["jobs"]   = do_jobs;
    m["bg"]     = do_bg;
    m["fg"]     = do_fg;
    m["ls"]     = do_ls;
}

void handle_signal(int sig) {
    for (;;) {
        int wstatus;
        int fd = waitpid(-1, &wstatus, WNOHANG | WUNTRACED | WCONTINUED);
        if (fd <= 0)
            break;
        // 进程号 -> 作业号
        if (pids.find(fd) == pids.end()) {
            printf("can't find fd: %d\n", fd);
            exit(-1);
            continue;
        }
        int jid = pids[fd];
        // 作业号 -> 作业
        if (jobs.find(jid) == jobs.end()) {
            list_job(-1);
            printf("can't find jid: %d \n", jid);
            exit(-1);
            continue;
        }
        // 作业中的进程
        if (jobs[jid].tasks.find(fd) == jobs[jid].tasks.end()) {
            printf("can't find fd(%d) in jid(%d)\n", fd, jid);
            exit(-1);
            continue;
        }
        if (WIFSTOPPED(wstatus)) {
            // 运行 -> 暂停
            ++jobs[jid].count_stop;
            --jobs[jid].count_run;
            jobs[jid].tasks[fd].status = STOP;
        } else if (WIFCONTINUED(wstatus)) {
            // 暂停 -> 运行
            --jobs[jid].count_stop;
            ++jobs[jid].count_run;
            jobs[jid].tasks[fd].status = RUN;
        } else {
            // 运行 或 暂停 -> 退出
            if (jobs[jid].tasks[fd].status == RUN)
                --jobs[jid].count_run;
            else
                --jobs[jid].count_stop;
            if (WIFSIGNALED(wstatus)) {
                ++jobs[jid].count_kill;
                jobs[jid].tasks[fd].status = KILL;
            } else {
                ++jobs[jid].count_done;
                jobs[jid].tasks[fd].status = DONE;
            }
        }
        if (tcgetpgrp(0) == jobs[jid].pgid && jobs[jid].count_run == 0) {
            // 当前的作业是前台作业, 而且要放弃前台进程组
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0, getpid());
            signal(SIGTTOU, SIG_DFL);
        }
    }
}

void init_signal_handle() {
    signal(SIGINT, SIG_IGN);         // ctrl+c
    signal(SIGQUIT, SIG_IGN);        // ctrl+/
    signal(SIGTSTP, SIG_IGN);        // ctrl+z
    signal(SIGCHLD, handle_signal);  // 子进程退出, 暂停, 继续
}

int run_cmd(cmd_t &cmd) {
    // 处理重定向
    if (handle_redirection(cmd) != 0)
        return -1;
    // 处理内置命令
    if (m.find(cmd.cmd_vec[0]) != m.end())
        return m[cmd.cmd_vec[0]](cmd);
    // 处理非内置命令
    char **argv;
    argv = (char **)malloc(sizeof(cmd.cmd_vec.size()) + 1);
    for (size_t i = 0; i < cmd.cmd_vec.size(); ++i)
        argv[i] = (char *)cmd.cmd_vec[i].data();
    argv[cmd.cmd_vec.size()] = NULL;
    execvp(argv[0], argv);
    perror(argv[0]);
    free(argv);
    return -1;
}

void run_cmd() {
    curr_jid = -1;     // 用于检测作业时, 输出不跳过当前作业
    if (cmds.empty())  // 命令为空, 直接跳过
        return;
    // 是否在当前进程处理
    if (fg && cmds.size() == 1 && cmds[0].in.empty() && cmds[0].out.empty() &&
        cmds[0].add.empty()) {
        // 非 管道 重定向 以及 后台命令, 才可能在当前进程中运行
        if (m.find(cmds[0].cmd_vec[0]) != m.end()) {
            m[cmds[0].cmd_vec[0]](cmds[0]);
            return;
        }
    }
    // 处理命令
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞所有信号
    job_t job;
    for (size_t i = 0; i < cmds.size(); ++i) {
        int pipe_fd[2];
        if (i + 1 != cmds.size() && pipe(pipe_fd) < 0) {
            // 不是最后一个命令需要新建管道
            perror("");
            return;
        }
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            setpgid(0, i == 0 ? 0 : job.pgid);  // 设置新的进程组
            if (i + 1 != cmds.size()) {
                // 将标准输出重定向到管道
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                if (pipe_fd[1] != STDOUT_FILENO)
                    close(pipe_fd[1]);
            }
            // 恢复信号处理
            signal(SIGINT, SIG_DFL);   // ctrl+c
            signal(SIGQUIT, SIG_DFL);  // ctrl+/
            signal(SIGTSTP, SIG_DFL);  // ctrl+z
            signal(SIGCHLD, SIG_DFL);  // 子进程退出, 暂停, 继续
            sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
            exit(run_cmd(cmds[i]));
        } else {
            // 父进程
            if (i == 0) {
                job.pgid       = fd;
                job.count_run  = cmds.size();
                job.count_stop = 0;
                job.count_kill = 0;
                job.count_done = 0;
                curr_jid       = next_jid++;
            }
            task_t task;
            task.cmd      = cmds[i].cmd_str;
            task.status   = RUN;
            job.tasks[fd] = task;
            pids[fd]      = curr_jid;

            setpgid(fd, job.pgid);  // 设置新的进程组

            if (i + 1 != cmds.size()) {
                // 将标准输入重定向到管道
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);
                if (pipe_fd[0] != STDIN_FILENO)
                    close(pipe_fd[0]);
            } else {
                // 将标准输入重定向到 /dev/tty
                int shell_tty = open("/dev/tty", O_RDONLY);
                dup2(shell_tty, STDIN_FILENO);
                if (shell_tty != STDIN_FILENO)
                    close(shell_tty);
            }
        }
    }

    jobs[curr_jid] = job;

    if (fg) {
        // 前台作业
        tcsetpgrp(0, job.pgid);  // 设置前台进程组
        while (tcgetpgrp(0) == job.pgid)
            sigsuspend(&mask_empty);  // 解阻塞信号, 然后暂停
    } else {
        list_job(curr_jid, true);
        curr_jid = -1;  // 用于检测作业时, 输出不跳过当前作业
    }
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
}

int main() {
    init_user_info();
    init_cmd_builtin();
    init_job();
    init_signal_handle();

    for (;;) {
        get_prompt();   // 获取提示符
        get_input();    // 获取用户输入
        parse_input();  // 解析命令行
        run_cmd();      // 运行命令
        check_job();    // 检测作业
    }

    return 0;
}
