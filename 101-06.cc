
#include "log.h"

int main() {
    init();

    double x = std::numeric_limits<double>::denorm_min();

    Double d(x);

    std::string str = d.double_by_cs;

    log();
    log("最小非规约正数: " + str);
    log("小数点后共有: " + std::to_string(str.size() - 2) + " 位");
    log();

    return 0;
}
