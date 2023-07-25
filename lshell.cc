
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

#define ARGV_SIZE 32    // 命令行参数的最大值
#define BUF_SIZE  1024  // 命令行的最大大小

std::string prompt;
char       *argv[ARGV_SIZE];
char        buf[BUF_SIZE + 1];

uid_t       user_id;
std::string user_name;
std::string user_home;

std::map<std::string, void (*)()> m;

void init();

void get_prompt();  // 获取命令行提示符
void get_cmd();
bool parse_cmd(char *curr_cmd);  // 解析命令行参数
void run_cmd();
void run_cmd(char *curr_cmd);

void do_about();
void do_exit();
void do_quit();
void do_cd();
void do_ulimit();

int main() {
    init();

    for (;;) {
        get_cmd();
        run_cmd();
    }

    return 0;
}

void init() {
    m["about"]  = do_about;
    m["exit"]   = do_exit;
    m["quit"]   = do_quit;
    m["cd"]     = do_cd;
    m["ulimit"] = do_ulimit;

    user_id            = getuid();
    struct passwd *pwd = getpwuid(user_id);

    user_name = pwd->pw_name;
    user_home = pwd->pw_dir;
}

// 获取命令行提示符
void get_prompt() {
    getcwd(buf, BUF_SIZE);
    std::string curr_dir = buf;

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

// 获取用户的输入，处理掉 ~ 代表目录的位置
void get_cmd() {
    get_prompt();  // 获取命令提示符

    char *p = readline(prompt.data());  // 读取一行，不包括 '\n'
    if (p == NULL) {                    // 读入 EOF
        printf("read EOF, exit\n");
        exit(EXIT_SUCCESS);
    }

    size_t pos_begin = 0;
    size_t pos_end   = strlen(p);

    while (pos_begin < pos_end && p[pos_begin] == ' ')
        ++pos_begin;
    while (pos_begin < pos_end && p[pos_end - 1] == ' ')
        --pos_end;

    std::string cmd;
    for (size_t i = pos_begin; i < pos_end; ++i) {
        if (p[i] != '~')
            cmd += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            cmd += user_home;
        else
            cmd += p[i];
    }

    free(p);  // 释放资源，避免内存泄漏

    if (cmd.size() > BUF_SIZE) {
        printf("too long cmd\n");
        buf[0] = '\0';
    } else {
        strcpy(buf, cmd.data());
        add_history(buf);
    }
}

// 解析命令行参数
bool parse_cmd(char *curr_cmd) {
    bool   new_argv   = true;  // 新参数开始
    size_t argv_index = 0;

    for (;;) {
        if (*curr_cmd == '\0') {
            argv[argv_index] = NULL;
            return true;
        }
        if (*curr_cmd == ' ') {
            *curr_cmd++ = '\0';
            new_argv    = true;
            continue;
        }
        if (*curr_cmd == '<') {
            *curr_cmd++ = '\0';
            new_argv    = true;
            while (*curr_cmd == ' ')
                ++curr_cmd;
            if (*curr_cmd == '\0') {
                printf("Please use: cmd < file_name\n");
                return false;
            }
            char *filename = curr_cmd;
            while (*curr_cmd != ' ' && *curr_cmd != '\0')
                ++curr_cmd;
            if (*curr_cmd != '\0')
                *curr_cmd++ = '\0';
            int fd = open(filename, O_RDONLY);
            if (fd < 0) {
                printf("can't open %s for: %s\n", filename, strerror(errno));
                return false;
            }
            dup2(fd, STDIN_FILENO);  // 将标准输入重定向到文件
            close(fd);
            continue;
        }
        if (*curr_cmd == '>') {
            *curr_cmd++ = '\0';
            new_argv    = true;

            bool add_to_file = false;
            if (*curr_cmd == '>') {
                add_to_file = true;
                ++curr_cmd;
            }
            while (*curr_cmd == ' ')
                ++curr_cmd;
            if (*curr_cmd == '\0') {
                printf(add_to_file ? "Please use cmd >  file_name\n"
                                   : "Please use cmd >> file_name\n");
                return false;
            }
            char *filename = curr_cmd;
            while (*curr_cmd != ' ' && *curr_cmd != '\0')
                ++curr_cmd;
            if (*curr_cmd != '\0')
                *curr_cmd++ = '\0';
            int fd = open(filename,
                          add_to_file ? (O_WRONLY | O_CREAT | O_APPEND)
                                      : (O_WRONLY | O_CREAT),
                          0644);
            if (fd < 0) {
                printf("can't open %s for: %s\n", filename, strerror(errno));
                return false;
            }
            dup2(fd, STDOUT_FILENO);  // 将标准输出重定向到文件
            close(fd);
            continue;
        }
        if (new_argv == true) {
            new_argv           = false;
            argv[argv_index++] = curr_cmd;
            if (argv_index >= ARGV_SIZE) {
                printf("too many arguments\n");
                return false;
            }
        }
        ++curr_cmd;
    }
}

void do_about() {
    printf("write by liuyunbin\n");
}

void do_exit() {
    exit(EXIT_SUCCESS);
}

void do_quit() {
    exit(EXIT_SUCCESS);
}

void do_cd() {
    const char *p;

    if (argv[1] == NULL) {
        p = user_home.data();
    } else if (argv[2] != NULL) {
        printf("cd: too many arguments\n");
        return;
    } else {
        p = argv[1];
    }
    if (chdir(p) == -1)
        printf("cd %s : %s\n", p, strerror(errno));
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

void do_ulimit() {
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

void run_cmd(char *curr_cmd) {
    if (parse_cmd(curr_cmd) == false)
        return;

    if (m.find(argv[0]) != m.end()) {
        m[argv[0]]();
    } else {
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }
}

void run_cmd() {
    if (strchr(buf, '|') == NULL && strchr(buf, '<') == NULL &&
        strchr(buf, '>') == NULL) {
        // 为求简单, 不存在管道和重定向时, 才可能在当前进程中运行
        size_t      len = strcspn(buf, " <>");
        std::string name(buf, len);
        if (m.find(name) != m.end()) {
            // 内置命令
            if (parse_cmd(buf))
                m[argv[0]]();
            return;
        }
    }

    if (fork() > 0) {
        wait(NULL);
        return;
    }

    char *next_cmd = strtok(buf, "|");

    for (;;) {
        char *curr_cmd = next_cmd;
        next_cmd       = strtok(NULL, "|");
        if (next_cmd == NULL) {
            run_cmd(curr_cmd);
        } else {
            int pipe_fd[2];
            if (pipe(pipe_fd) < 0) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
            if (fork() == 0) {  // 子进程
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);  // 将标准输出重定向到管道
                close(pipe_fd[1]);
                run_cmd(curr_cmd);
            } else {  // 父进程
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);  // 将标准输入重定向到管道
                close(pipe_fd[1]);
                wait(NULL);
            }
        }
    }
}
