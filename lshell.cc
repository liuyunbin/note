
//本程序用于实现 Linux 命令行 shell
//
//#### 项目流程：
// 1. 设置命令行前缀，并输出
// 2. 读取用户的输入，忽略所有的前置空格，并取代所有的 ~
// 表示用户主目录的地方，包括 “\~”，“\~\/”
// 3. 如果用户输入为空，跳到第 1 步
// 4. 如果用户输入是内置命令：“cd” 或 “about”，在当前进程执行命令，而后，跳到第
// 1 步
// 5. 如果用户输入是内置命令：“exit” 或 “quit”，直接退出进程
// 6. 如果用户输入的是系统命令，fork 子进程，
//    * 父进程 wait 子进程
//    * 子进程使用管道（|）对用户输入的命令进行切割，获取当前命令，
//        * 如果还有下一条命令，则建立管道，fork 子进程，
//            * 子进程将标准输出重定向到管道，然后对当前命令进行解析，而后执行命令
//            * 父进程将标准输入重定向到管道，然后 wait
//            子进程，而后读取下一条命令
//        * 如果这是最后一条命令，对当前命令进行解析，而后执行命令，然后，跳到第
//        1 步
//
//**说明：**
//* 对命令进行解析是指：获取参数，并处理 “<” “>”  “>>”，将标准输入 或
//输出重定向到文件
//* 由于本项目是，先处理管道，后处理其它重定向，所以，当存在其它重定向时，管道将失效

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
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#define BUF_SIZE 4096

#define ARGV_SIZE_MAX 32  // 命令行参数的最大值

#define COMMAND_SIZE_MAX 1024  // 命令行的最大大小

std::string cmd;
std::string prompt;

// 获取命令行提示符
void get_prompt() {
    uid_t          user_id = getuid();
    struct passwd *pwd     = getpwuid(user_id);

    prompt                    = pwd->pw_name;  // user name
    std::string user_home_dir = pwd->pw_dir;

    char       *p           = get_current_dir_name();
    std::string current_dir = p;
    free(p);  // 及时释放，避免内存泄漏

    prompt += ":";

    if (current_dir == user_home_dir) {
        prompt += "~";
    } else if (current_dir < user_home_dir) {
        prompt += current_dir;
    } else if (current_dir.compare(0, user_home_dir.size(), user_home_dir) !=
               0) {
        prompt += current_dir;
    } else if (current_dir[user_home_dir.size()] != '/') {
        prompt += current_dir;
    } else {
        prompt += '~';
        prompt += current_dir.data() + user_home_dir.size();
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
    if (p == NULL)                      // 读入 EOF
        exit(EXIT_FAILURE);
    if (p[0] != '\0')
        add_history(p);
    uid_t          user_id = getuid();
    struct passwd *pwd     = getpwuid(user_id);

    cmd = "";
    for (size_t i = 0; p[i] != '\0'; ++i) {
        if (p[i] != '~')
            cmd += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            cmd += pwd->pw_dir;  // user home directory
        else
            cmd += p[i];
    }

    free(p);  // 释放资源，避免内存泄漏
}

bool run_builtin_cmd() {
    char buffer_cmd[COMMAND_SIZE_MAX + 1];
    strcpy(buffer_cmd, cmd.data());
    std::string user_cmd = strtok(buffer_cmd, " ");

    if (user_cmd == "exit" || user_cmd == "quit")
        exit(EXIT_SUCCESS);
    if (user_cmd == "about") {
        printf("write by liuyunbin\n");
        return true;
    }
    if (user_cmd == "cd") {
        char *argument = strtok(NULL, " ");
        if (argument == NULL) {
            struct passwd *pwd = getpwuid(getuid());
            argument           = pwd->pw_dir;
        } else if (strtok(NULL, " ") != NULL) {
            printf("cd: too many arguments\n");
            return true;
        }
        if (chdir(argument) == -1)
            printf("cd %s : %s\n", argument, strerror(errno));
        return true;
    }
    return false;
}

// 解析命令行参数
void parse_cmd(char **argv, size_t argv_size_max, char *current_cmd) {
    bool   new_argv   = true;  // 新参数开始
    size_t argv_index = 0;

    for (;;) {
        if (*current_cmd == '\0') {
            argv[argv_index] = NULL;
            return;
        }
        if (isspace(*current_cmd)) {
            *current_cmd++ = '\0';
            new_argv       = true;
            continue;
        }
        if (*current_cmd == '<') {
            ++current_cmd;
            while (isspace(*current_cmd))
                ++current_cmd;
            if (*current_cmd == '\0') {
                printf("Please use: cmd < file_name\n");
                exit(EXIT_FAILURE);
            }
            char *filename = current_cmd;
            while (!isspace(*current_cmd) && *current_cmd != '\0')
                ++current_cmd;
            if (*current_cmd != '\0')
                *current_cmd++ = '\0';
            int fd = open(filename, O_RDONLY);
            if (fd < 0) {
                printf("can't open %s for: %s\n", filename, strerror(errno));
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);  // 将标准输入重定向到文件
            close(fd);
            continue;
        }
        if (*current_cmd == '>') {
            bool add_to_file = false;
            if (*++current_cmd == '>') {
                add_to_file = true;
                ++current_cmd;
            }
            while (isspace(*current_cmd))
                ++current_cmd;
            if (*current_cmd == '\0') {
                printf(add_to_file ? "Please use cmd >  file_name\n"
                                   : "Please use cmd >> file_name\n");
                exit(EXIT_FAILURE);
            }
            char *filename = current_cmd;
            while (!isspace(*current_cmd) && *current_cmd != '\0')
                ++current_cmd;
            if (*current_cmd != '\0')
                *current_cmd++ = '\0';
            int fd = open(filename,
                          add_to_file ? (O_WRONLY | O_CREAT | O_APPEND)
                                      : (O_WRONLY | O_CREAT),
                          0644);
            if (fd < 0) {
                printf("can't open %s for: %s\n", filename, strerror(errno));
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);  // 将标准输出重定向到文件
            close(fd);
            continue;
        }
        if (new_argv == true) {
            new_argv           = false;
            argv[argv_index++] = current_cmd;
            if (argv_index >= argv_size_max) {
                printf("too many arguments\n");
                exit(EXIT_FAILURE);
            }
        }
        ++current_cmd;
    }
}

void run_cmd() {
    // 移除行首的空字符
    std::size_t index = cmd.find_first_not_of(' ');
    if (index == std::string::npos)
        return;
    cmd = cmd.substr(index);

    if (cmd.size() > COMMAND_SIZE_MAX) {
        printf("命令行过长\n");
        return;
    }

    if (run_builtin_cmd() == true)
        return;

    if (fork() > 0) {
        wait(NULL);
        return;
    }

    char buffer_cmd[COMMAND_SIZE_MAX + 1];
    strcpy(buffer_cmd, cmd.data());

    char *next_cmd = strtok(buffer_cmd, "|");
    char *argv[ARGV_SIZE_MAX];

    for (;;) {
        char *current_cmd = next_cmd;
        next_cmd          = strtok(NULL, "|");
        if (next_cmd == NULL) {
            parse_cmd(argv, ARGV_SIZE_MAX, current_cmd);
            execvp(argv[0], argv);
            perror("");
            exit(EXIT_FAILURE);
        } else {
            int pipe_fd[2];
            if (pipe(pipe_fd) < 0) {
                perror("");
                exit(EXIT_FAILURE);
            }
            if (fork() == 0) {  // 子进程
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);  // 将标准输出重定向到管道
                close(pipe_fd[1]);
                parse_cmd(argv, ARGV_SIZE_MAX, current_cmd);
                execvp(argv[0], argv);
                perror("");
                exit(EXIT_FAILURE);
            } else {  // 父进程
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);  // 将标准输入重定向到管道
                close(pipe_fd[1]);
                wait(NULL);
            }
        }
    }
}

int main() {
    for (;;) {
        get_cmd();
        run_cmd();
    }

    return 0;
}
