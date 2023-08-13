
#include <fcntl.h>             // open
#include <readline/history.h>  // add_history
#include <sys/stat.h>          // open
#include <sys/types.h>         // open
#include <unistd.h>            // dup2

#include "lshell.h"

int parse_cmd(std::string str, std::vector<cmd_t> &cmds) {
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

int parse_input(std::string input, std::vector<cmd_t> &cmds, bool &fg) {
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
            return -1;
        }
        std::string str;
        while (i < input.size() && input[i] != '|')
            str.push_back(input[i++]);
        if (parse_cmd(str) != 0)
            return -1;
    }
    return 0;
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

int run_cmd(const cmd_t &cmd) {
    // 处理重定向
    if (handle_redirection(cmd) != 0)
        return -1;
    // 处理内置命令
    if (is_cmd_builtin(cmd))
        return run_cmd_builtin(cmd);
    // 处理测试命令
    if (is_cmd_test(cmd))
        return run_cmd_test(cmd);
    // 处理非内置 测试命令
    char **argv = (char **)malloc(sizeof(cmd.vec.size()) + 1);
    for (size_t i = 0; i < cmd.vec.size(); ++i)
        argv[i] = (char *)cmd.vec[i].data();
    argv[cmd.vec.size()] = NULL;
    execvp(argv[0], argv);
    perror(argv[0]);
    free(argv);
    return -1;
}
