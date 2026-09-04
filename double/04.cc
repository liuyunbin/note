
#include "log.h"

int main() {
    log();
    log("测试存储时的四舍六入五取偶");
    log();

    log("        舍入方向: " + dict_round[fegetround()]);

    test_double(
        "测试 最后一位是 0, 多余位是 10(舍, 取偶)",
        "0100000000000000000000000000000000000000000000000000000000000000 10");

    log();
    log("主进程正常退出");
    log();
    return 0;
}
