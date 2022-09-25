
#include "bash.h"

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

std::string command;
std::string prompt;

// 获取命令行提示符
void get_prompt() {
    uid_t user_id = getuid();
    struct passwd *pwd = getpwuid(user_id);

    prompt = pwd->pw_name;  // user name
    std::string user_home_dir = pwd->pw_dir;

    char *p = get_current_dir_name();
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
void get_command() {
    get_prompt();  // 获取命令提示符

    char *p = readline(prompt.data());  // 读取一行，不包括 '\n'
    if (p == NULL)                      // 读入 EOF
        exit(EXIT_FAILURE);
    if (p[0] != '\0') add_history(p);
    uid_t user_id = getuid();
    struct passwd *pwd = getpwuid(user_id);

    command = "";
    for (size_t i = 0; p[i] != '\0'; ++i) {
        if (p[i] != '~')
            command += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            command += pwd->pw_dir;  // user home directory
        else
            command += p[i];
    }

    free(p);  // 释放资源，避免内存泄漏
}

bool run_builtin_command() {
    char buffer_command[COMMAND_SIZE_MAX + 1];
    strcpy(buffer_command, command.data());
    std::string user_command = strtok(buffer_command, " ");

    if (user_command == "exit" || user_command == "quit") exit(EXIT_SUCCESS);
    if (user_command == "about") {
        printf("write by liuyunbin\n");
        return true;
    }
    if (user_command == "cd") {
        char *argument = strtok(NULL, " ");
        if (argument == NULL) {
            struct passwd *pwd = getpwuid(getuid());
            argument = pwd->pw_dir;
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
void parse_command(char **argv, size_t argv_size_max, char *current_command) {
    bool new_argv = true;  // 新参数开始
    size_t argv_index = 0;

    for (;;) {
        if (*current_command == '\0') {
            argv[argv_index] = NULL;
            return;
        }
        if (isspace(*current_command)) {
            *current_command++ = '\0';
            new_argv = true;
            continue;
        }
        if (*current_command == '<') {
            ++current_command;
            while (isspace(*current_command)) ++current_command;
            if (*current_command == '\0') {
                printf("Please use: command < file_name\n");
                exit(EXIT_FAILURE);
            }
            char *filename = current_command;
            while (!isspace(*current_command) && *current_command != '\0')
                ++current_command;
            if (*current_command != '\0') *current_command++ = '\0';
            int fd = open(filename, O_RDONLY);
            if (fd < 0) {
                printf("can't open %s for: %s\n", filename, strerror(errno));
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);  // 将标准输入重定向到文件
            close(fd);
            continue;
        }
        if (*current_command == '>') {
            bool add_to_file = false;
            if (*++current_command == '>') {
                add_to_file = true;
                ++current_command;
            }
            while (isspace(*current_command)) ++current_command;
            if (*current_command == '\0') {
                printf(add_to_file ? "Please use command >  file_name\n"
                                   : "Please use command >> file_name\n");
                exit(EXIT_FAILURE);
            }
            char *filename = current_command;
            while (!isspace(*current_command) && *current_command != '\0')
                ++current_command;
            if (*current_command != '\0') *current_command++ = '\0';
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
            new_argv = false;
            argv[argv_index++] = current_command;
            if (argv_index >= argv_size_max) {
                printf("too many arguments\n");
                exit(EXIT_FAILURE);
            }
        }
        ++current_command;
    }
}

void run_command() {
    // 移除行首的空字符
    std::size_t index = command.find_first_not_of(' ');
    if (index == std::string::npos) return;
    command = command.substr(index);

    if (command.size() > COMMAND_SIZE_MAX) {
        printf("命令行过长\n");
        return;
    }

    if (run_builtin_command() == true) return;

    if (fork() > 0) {
        wait(NULL);
        return;
    }

    char buffer_command[COMMAND_SIZE_MAX + 1];
    strcpy(buffer_command, command.data());

    char *next_command = strtok(buffer_command, "|");
    char *argv[ARGV_SIZE_MAX];

    for (;;) {
        char *current_command = next_command;
        next_command = strtok(NULL, "|");
        if (next_command == NULL) {
            parse_command(argv, ARGV_SIZE_MAX, current_command);
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
                parse_command(argv, ARGV_SIZE_MAX, current_command);
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
