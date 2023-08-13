
#include "lshell.h"

int main() {
    init_user_info();
    init_cmd_builtin();
    init_job();
    init_signal_handle();

    for (;;) {
        get_prompt();   // 获取提示符
        get_input();    // 获取用户输入
        parse_input();  // 解析命令行
        run_cmd();      // 运行命令
        check_job();    // 检测作业
    }

    return 0;
}
