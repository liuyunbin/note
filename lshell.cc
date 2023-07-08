
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

class lshell {
  public:
    lshell();
    void get_cmd();  // 获取命令

  private:
    uid_t       user_id;        // 用户 ID
    std::string user_name;      // 用户名称
    std::string user_home_dir;  // 用户主目录

    std::string cmd;

    std::string get_prompt();  // 获取命令行提示符
};

#define BUF_SIZE      4096
#define ARGV_SIZE_MAX 32  // 命令行参数的最大值

int main() {
    //    lshell s;

    for (;;) {
        //        s.get_cmd();
        //        s.run_cmd();
    }

    return 0;
}

#if 0
lshell::lshell() {
    user_id            = getuid();  // 用户 ID
    struct passwd *pwd = getpwuid(user_id);
    user_name          = pwd->pw_name;  // 用户名称
    user_home_dir      = pwd->pw_dir;   // 用户主目录
}

// 获取命令行提示符
std::string lshell::get_prompt() {
    std::string prompt = user_name + ":";

    char       *p           = get_current_dir_name();
    std::string current_dir = p;
    free(p);  // 及时释放，避免内存泄漏

    if (current_dir == user_home_dir) {
        prompt += "~";
    } else if (current_dir < user_home_dir) {
        prompt += current_dir;
    } else if (current_dir.substr(0, user_home_dir.size()) != user_home_dir) {
        prompt += current_dir;
    } else if (current_dir[user_home_dir.size()] != '/') {
        prompt += current_dir;
    } else {
        prompt += '~';
        prompt += current_dir.substr(user_home_dir.size());
    }

    if (user_id == 0)
        prompt += "# ";
    else
        prompt += "$ ";
}

// 获取用户的输入
void lshell::get_cmd() {
    std::string prompt = get_prompt();  // 获取命令提示符

    char *p = readline(prompt.data());  // 读取一行，不包括 '\n'
    if (p == NULL)                      // 读入 EOF
        exit(EXIT_FAILURE);

    cmd = "";
    // 处理掉 ~ 代表目录的位置
    for (size_t i = 0; p[i] != '\0'; ++i) {
        if (p[i] != '~')
            cmd += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            cmd += user_home_dir;
        else
            cmd += p[i];
    }

    free(p);  // 释放资源，避免内存泄漏

    // 去掉前缀空格
    size_t index = cmd.find_first_not_of(' ');
    cmd          = cmd.substr(index);
}

// 解析命令行参数
void lshell::parse_command(char **argv,
                           size_t argv_size_max,
                           char  *current_command) {
    bool   new_argv   = true;  // 新参数开始
    size_t argv_index = 0;

    for (;;) {
        if (*current_command == '\0') {
            argv[argv_index] = NULL;
            return;
        }
        if (isspace(*current_command)) {
            *current_command++ = '\0';
            new_argv           = true;
            continue;
        }
        if (*current_command == '<') {
            ++current_command;
            while (isspace(*current_command))
                ++current_command;
            if (*current_command == '\0') {
                printf("Please use: command < file_name\n");
                exit(EXIT_FAILURE);
            }
            char *filename = current_command;
            while (!isspace(*current_command) && *current_command != '\0')
                ++current_command;
            if (*current_command != '\0')
                *current_command++ = '\0';
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
            while (isspace(*current_command))
                ++current_command;
            if (*current_command == '\0') {
                printf(add_to_file ? "Please use command >  file_name\n"
                                   : "Please use command >> file_name\n");
                exit(EXIT_FAILURE);
            }
            char *filename = current_command;
            while (!isspace(*current_command) && *current_command != '\0')
                ++current_command;
            if (*current_command != '\0')
                *current_command++ = '\0';
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
            argv[argv_index++] = current_command;
            if (argv_index >= argv_size_max) {
                printf("too many arguments\n");
                exit(EXIT_FAILURE);
            }
        }
        ++current_command;
    }
}

bool run_builtin_command() {
    char buffer_command[1024 + 1];
    strcpy(buffer_command, command.data());
    std::string user_command = strtok(buffer_command, " ");

    if (user_command == "ulimit") {
        do_ulimit();
        return true;
    }

    if (user_command == "exit" || user_command == "quit")
        exit(EXIT_SUCCESS);
    if (user_command == "about") {
        printf("write by liuyunbin\n");
        return true;
    }
    if (user_command == "cd") {
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

void lshell::run_command() {
    if (command == "")
        return;
    add_history(p);

    if (command.size() > 1024) {
        printf("命令行过长\n");
        return;
    }

    if (run_builtin_command() == true)
        return;

    if (fork() > 0) {
        wait(NULL);
        return;
    }

    char buffer_command[1024];
    strcpy(buffer_command, command.data());

    char *next_command = strtok(buffer_command, "|");
    char *argv[ARGV_SIZE_MAX];

    for (;;) {
        char *current_command = next_command;
        next_command          = strtok(NULL, "|");
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

#define GET_LIMIT(X)                            \
    {                                           \
        struct rlimit rlim;                     \
        getrlimit(X, &rlim);                    \
        printf("  资源: %s\n", #X);             \
        printf("软限制: %ld\n", rlim.rlim_cur); \
        printf("硬限制: %ld\n", rlim.rlim_max); \
    }

void do_ulimit() {
    GET_LIMIT(RLIMIT_CORE);
}

int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);
#endif
