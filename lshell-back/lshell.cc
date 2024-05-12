
#if 0
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <map>
#include <vector>

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

    if (m.find(argv[0]) != m.end()) {
        // 处理内置命令
        ret = m[argv[0]](argc, argv);
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

    sigaddset(&mask_child, SIGCHLD);
    sigemptyset(&mask_empty);

    // 初始化状态名称
    status[RUN]  = "run   ";
    status[STOP] = "stop  ";
    status[KILL] = "killed";
    status[DONE] = "done  ";
}

#endif
