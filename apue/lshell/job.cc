
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
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
#include <stack>
#include <utility>

#include "lshell.h"

// 作业
enum status_t {
    BG,    // 后台
    FG,    // 前台
    RUN,   // 运行
    STOP,  // 暂停
    KILL,  // 杀死
    DONE   // 完成
};

std::string status_to_string(status_t st) {
    if (st == RUN)
        return "run   ";
    else if (st == STOP)
        return "stop  ";
    else if (st == KILL)
        return "killed";
    else if (st == DONE)
        return "done  ";
    return "";
}

struct task_t {
    std::string cmd;     // 进程命令
    status_t    status;  // 进程状态
};

struct job_t {
    pid_t                   pgid;        // 进程组 ID
    status_t                st;          // 前台还是后台
    int                     count_run;   // 进程数 -- 运行
    int                     count_stop;  // 进程数 -- 暂停
    int                     count_kill;  // 进程数 -- 杀死
    int                     count_done;  // 进程数 -- 退出
    std::map<pid_t, task_t> tasks;       // 任务的进程信息
};

std::map<int, job_t> jobs;          // 作业
std::map<pid_t, int> pids;          // 进程号 -> 作业号
int                  next_jid = 1;  // 下一个可用的作业号

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
        std::string status;
        std::string cmd;
        if (not no_status) {
            status = status_to_string(it.second.status);
            cmd    = it.second.cmd;
        }

        if (first) {
            first = false;
            printf("[%d] %d %s %s\n", jid, it.first, status.data(), cmd.data());
        } else {
            printf("[%c] %d %s %s\n", ' ', it.first, status.data(), cmd.data());
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

void run_job(const std::vector<cmd_t> &cmds) {
    if (cmds.empty())  // 命令为空, 直接跳过
        return;
    // 是否在当前进程处理
    if (fg && cmds.size() == 1 && cmds[0].in.empty() && cmds[0].out.empty() &&
        cmds[0].add.empty()) {
        // 非 管道 重定向 以及 后台命令, 才可能在当前进程中运行
        if (is_builtin_cmd(cmds[0])) {
            run_builtin_cmd(cmds[0]);
            return;
        }
    }
    // 处理命令
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞所有信号
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
                close(pipe_fd[0]);
            } else {
                // 将标准输入重定向到 /dev/tty
                int shell_tty = open("/dev/tty", O_RDONLY);
                dup2(shell_tty, STDIN_FILENO);
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
