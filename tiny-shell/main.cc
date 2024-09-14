
#include "lshell.h"

int main() {
    std::string        input;
    std::vector<cmd_t> cmds;
    bool               fg;

    init_signal();
    init_builtin();
    init_test_cmd();
    init_jobs();

    for (;;) {
        input = get_input();            // 获取用户输入
        handle_input(cmds, fg, input);  // 解析用户输入
        handle_jobs(cmds, fg);          // 执行用户输入
        check_jobs();                   // 检查已完成的作业
    }

    return 0;
}
