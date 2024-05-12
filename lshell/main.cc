
#include "lshell.h"

uid_t       user_id;    // 用户 ID
std::string user_name;  // 用户 名称
std::string user_home;  // 用户 主目录

// 用户输入
std::string input;

void get_input() {
    // 用户提示符
    std::string prompt = get_prompt();  // 获取用户提示符
    char*       p      = readline(prompt.data());

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

std::vector<cmd_t> cmds;  // 用户输入 -> 命令数组
bool               fg;    // 前台还是后台作业

// 解析单个命令
int parse_cmd(std::string& str) {
    while (!str.empty() && str.back() == ' ')
        str.pop_back();
    cmd_t cmd;
    cmd.str = str;
    for (size_t i = 0; i < str.size();) {
        while (i < str.size() && str[i] == ' ')
            ++i;
        if (i >= str.size())
            break;
        if (str[i] == '<') {
            while (++i < str.size() && str[i] == ' ')
                ;
            if (cmd.vec.empty() || i >= str.size()) {
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
            if (cmd.vec.empty() || i >= str.size()) {
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
        cmd.vec.push_back(name);
    }
    cmds.push_back(cmd);
    return 0;
}

// 解析用户输入
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
    for (size_t i = 0; i < input.size(); ++i) {
        while (i < input.size() && input[i] == ' ')
            ++i;
        if (i >= input.size())
            break;
        if (input[i] == '|') {
            printf("invalid cmd!\n");
            cmds.clear();
            return;
        }
        std::string str;
        while (i < input.size() && input[i] != '|')
            str.push_back(input[i++]);
        if (parse_cmd(str) != 0) {
            cmds.clear();
            return;
        }
    }
}

// 处理重定向
int handle_redirection(const std::string& filename, int flag, int fd_new) {
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

int handle_redirection(const cmd_t& cmd) {
    // 输入重定向
    if (handle_redirection(cmd.in, O_RDONLY, STDIN_FILENO) != 0)
        return -1;
    // 输出重定向
    if (handle_redirection(cmd.out,
                           O_WRONLY | O_CREAT | O_TRUNC,
                           STDOUT_FILENO) != 0)
        return -1;
    // 添加重定向
    if (handle_redirection(cmd.add,
                           O_WRONLY | O_CREAT | O_APPEND,
                           STDOUT_FILENO) != 0)
        return -1;
    return 0;
}

// 运行命令
int run_cmd(const cmd_t& cmd) {
    // 处理重定向
    if (handle_redirection(cmd) != 0)
        return -1;
    int    argc = cmd.vec.size();
    char** argv = (char**)malloc(sizeof(cmd.vec.size()) + 1);
    for (size_t i = 0; i < cmd.vec.size(); ++i)
        argv[i] = (char*)cmd.vec[i].data();
    argv[cmd.vec.size()] = NULL;
    int ret;

    if (is_builtin(cmd)) {
        // 处理内置命令
        ret = run_builtin(argc, argv);
    } else {
        // 处理非内置命令
        ret = execvp(argv[0], argv);
        perror(argv[0]);
    }
    free(argv);
    return ret;
}

// 作业
enum status_t {
    BG,    // 后台
    FG,    // 前台
    RUN,   // 运行
    STOP,  // 暂停
    KILL,  // 杀死
    DONE   // 完成
};

struct task_t {
    std::string cmd;     // 进程命令
    status_t    status;  // 进程状态
};

struct job_t {
    int                     jid;         // 作业号
    pid_t                   pgid;        // 进程组 ID
    status_t                status;      // 前台还是后台
    int                     count_run;   // 进程数 -- 运行
    int                     count_stop;  // 进程数 -- 暂停
    int                     count_kill;  // 进程数 -- 杀死
    int                     count_done;  // 进程数 -- 退出
    std::map<pid_t, task_t> tasks;       // 任务的进程信息
};

std::map<status_t, std::string> status;        // 状态 => 字符串
std::map<int, job_t>            jobs;          // 作业号 => 作业
std::map<pid_t, int>            pids;          // 进程号 -> 作业号
int                             next_jid = 1;  // 下一个可用的作业号

sigset_t mask_child;
sigset_t mask_empty;

void handle_signal(int sig) {
    for (;;) {
        int wstatus;
        int fd = waitpid(-1, &wstatus, WNOHANG | WUNTRACED | WCONTINUED);
        if (fd <= 0)
            break;
        // 进程号 -> 作业号
        if (pids.find(fd) == pids.end()) {
            printf("can't find fd: %d\n", fd);
            continue;
        }
        int jid = pids[fd];
        // 作业号 -> 作业
        if (jobs.find(jid) == jobs.end()) {
            printf("can't find jid: %d \n", jid);
            continue;
        }
        // 作业中的进程
        if (jobs[jid].tasks.find(fd) == jobs[jid].tasks.end()) {
            printf("can't find fd(%d) in jid(%d)\n", fd, jid);
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

            if (jobs[jid].count_stop != 0) {
                // 此作业还没做完, 还有任务处于暂停状态
                jobs[jid].status = BG;
            }

            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0, getpid());
            signal(SIGTTOU, SIG_DFL);
        }
    }
}

// 调用此函数前需要阻塞 SIGCHLD
// 此时, 主进程一定是前台进程组
int list_job(int jid, bool no_status = false) {
    if (jid == -1) {
        for (auto& it : jobs)
            list_job(it.first, no_status);
        return 0;
    }
    if (jobs.find(jid) == jobs.end()) {
        printf("can't find job %d\n", jid);
        return -1;
    }
    bool first = true;
    for (auto it : jobs[jid].tasks) {
        std::string st;
        std::string cmd;
        if (not no_status) {
            st  = status[it.second.status];
            cmd = it.second.cmd;
        }

        if (first) {
            first = false;
            printf("[%d] %d %s %s\n", jid, it.first, st.data(), cmd.data());
        } else {
            printf("[%c] %d %s %s\n", ' ', it.first, st.data(), cmd.data());
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
        if (it->second.status != FG)
            list_job(it->first);
        // 删除进程号到作业号的映射
        for (auto& v : it->second.tasks)
            pids.erase(v.first);
        // 删除此作业
        it = jobs.erase(it);
        // 修正下一个可以使用的作业号
        next_jid = 0;
        for (auto& v : jobs)
            next_jid = std::max(v.first, next_jid);
        ++next_jid;
    }
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
}

int do_jobs(int argc, char* argv[]) {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    list_job(-1);
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

int do_bg(int argc, char* argv[]) {
    if (argc != 2) {
        printf("please use bg jid\n");
        return -1;
    }
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    int jid = atoi(argv[1]);
    if (jobs.find(jid) == jobs.end()) {
        printf("job not find: %d\n", jid);
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    kill(-jobs[jid].pgid, SIGCONT);
    printf("[%d] running\n", jid);
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

int do_fg(int argc, char* argv[]) {
    if (argc != 2) {
        printf("please use fg jid\n");
        return -1;
    }
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    int jid = atoi(argv[1]);
    if (jobs.find(jid) == jobs.end()) {
        printf("job not find: %d\n", jid);
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    jobs[jid].status = FG;
    tcsetpgrp(0, jobs[jid].pgid);
    kill(-jobs[jid].pgid, SIGCONT);
    while (tcgetpgrp(0) == jobs[jid].pgid)
        sigsuspend(&mask_empty);  // 解阻塞信号, 然后暂停
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

void handle_job() {
    if (cmds.empty())  // 命令为空, 直接跳过
        return;
    // 是否在当前进程处理
    if (fg && cmds.size() == 1 && cmds[0].in.empty() && cmds[0].out.empty() &&
        cmds[0].add.empty()) {
        // 非 管道 重定向 以及 后台命令, 才可能在当前进程中运行
        if (is_builtin(cmds[0])) {  // 是否是内置命令
            run_cmd(cmds[0]);
            return;
        }
    }
    // 处理命令
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    job_t job;
    for (size_t i = 0; i < cmds.size(); ++i) {
        int pipe_fd[2];
        if (i + 1 != cmds.size())  // 不是最后一个命令需要新建管道
            pipe(pipe_fd);
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            setpgid(0, i == 0 ? 0 : job.pgid);  // 设置新的进程组
            if (i + 1 != cmds.size()) {
                // 将标准输出重定向到管道
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
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
                job.jid        = next_jid++;
                job.pgid       = fd;
                job.status     = fg ? FG : BG;
                job.count_run  = cmds.size();
                job.count_stop = 0;
                job.count_kill = 0;
                job.count_done = 0;
            }
            task_t task;
            task.cmd      = cmds[i].str;
            task.status   = RUN;
            job.tasks[fd] = task;
            pids[fd]      = job.jid;

            setpgid(fd, job.pgid);  // 设置新的进程组

            if (i + 1 != cmds.size()) {
                // 将标准输入重定向到管道
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);
                close(pipe_fd[0]);
            } else {
                // 将标准输入重定向到 /dev/tty
                int shell_tty = open("/dev/tty", O_RDONLY);
                dup2(shell_tty, STDIN_FILENO);
                close(shell_tty);
            }
        }
    }

    jobs[job.jid] = job;

    if (fg) {
        // 前台作业
        tcsetpgrp(0, job.pgid);  // 设置前台进程组
        while (tcgetpgrp(0) == job.pgid)
            sigsuspend(&mask_empty);  // 解阻塞信号, 然后暂停
    } else {
        list_job(job.jid, true);
    }
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
}

void init() {
    // 初始化用户信息
    user_id = getuid();

    struct passwd* pw_ptr = getpwuid(user_id);
    if (pw_ptr != NULL) {
        user_name = std::string(pw_ptr->pw_name);
        user_home = std::string(pw_ptr->pw_dir);
    } else {
        user_name = std::to_string(user_id);
    }

    // 初始化信号
    signal(SIGINT, SIG_IGN);         // ctrl+c
    signal(SIGQUIT, SIG_IGN);        // ctrl+/
    signal(SIGTSTP, SIG_IGN);        // ctrl+z
    signal(SIGCHLD, handle_signal);  // 子进程退出, 暂停, 继续

    sigaddset(&mask_child, SIGCHLD);
    sigemptyset(&mask_empty);

    // 初始化状态名称
    status[RUN]  = "run   ";
    status[STOP] = "stop  ";
    status[KILL] = "killed";
    status[DONE] = "done  ";
}

int main() {
    init_builtin();
    init();

    for (;;) {
        get_input();    // 获取用户输入
        parse_input();  // 解析用户输入
        handle_job();   // 处理作业
        check_job();    // 检查已完成的作业
    }

    return 0;
}
