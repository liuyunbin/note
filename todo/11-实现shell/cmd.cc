
#include "lshell.h"

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
    } else if (is_test_cmd(cmd)) {
        // 处理测试命令
        ret = run_test_cmd(argc, argv);
    } else {
        // 处理非内置命令
        ret = execvp(argv[0], argv);
        perror(argv[0]);
    }
    free(argv);
    return ret;
}
