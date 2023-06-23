
#include "log.h"

int main() {
    log();
    log("测试浮点数能表示的最大的小数点后的位数");
    log();

    double x = std::numeric_limits<double>::denorm_min();

    Double d(x);

    std::string str = d.double_by_cs;

    log("最小非规约正数: " + str);
    log("小数点后共有: " + std::to_string(str.size() - 2) + " 位");

    log();
    log("主进程正常退出");
    log();
    return 0;
}
