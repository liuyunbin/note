
#include "log.h"

int main() {
    log();
    log("测试 round()");
    log();

    log("        舍入方向: " + dict_round[fegetround()]);
    test_round("1.5", 1.5);
    test_round("2.5", 2.5);
    test_round("3.5", 3.5);

    test_double("1", 1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
