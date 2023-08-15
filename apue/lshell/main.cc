
#include "lshell.h"

int main() {
    init_cmd_builtin();  // 初始化内置命令
    init_cmd_test();     // 初始化测试命令
    init_job();          // 初始化作业

    std::string        input;  // 用户输入
    std::vector<cmd_t> cmds;   // 用户输入 -> 命令数组
    bool               fg;     // 前台还是后台作业

    for (;;) {
        get_input(input);              // 获取用户输入
        parse_input(input, cmds, fg);  // 解析用户输入
        handle_job(cmds, fg);          // 处理作业
        check_job();                   // 检查已完成的作业
    }

    return 0;
}
