
#include "log.h"

int main() {
    log();
    log("测试不同类型的浮点数以及浮点数的差值");
    log();

    test_double(
        "正零",
        "0 00000000000 0000000000000000000000000000000000000000000000000000");
    test_double(
        "最小非规约正数",
        "0 00000000000 0000000000000000000000000000000000000000000000000001");
    test_double(
        "最大非规约正数",
        "0 00000000000 1111111111111111111111111111111111111111111111111111");
    test_double(
        "最小  规约正数",
        "0 00000000001 0000000000000000000000000000000000000000000000000000");
    test_double(
        "最大  规约正数",
        "0 11111111110 1111111111111111111111111111111111111111111111111111");
    test_double(
        "正无穷",
        "0 11111111111 0000000000000000000000000000000000000000000000000000");
    test_double(
        "非数字",
        "0 11111111111 0000000000000000000000000000000000000000000000000001");

    log();
    log("使用 numeric_limits");
    log("最小非规约负数: " + Double(std::numeric_limits<double>::lowest()).bit);
    log("最小非规约正数: " +
        Double(std::numeric_limits<double>::denorm_min()).bit);
    log("最小  规约正数: " + Double(std::numeric_limits<double>::min()).bit);
    log("最大  规约正数: " + Double(std::numeric_limits<double>::max()).bit);
    log("        正无穷: " +
        Double(std::numeric_limits<double>::infinity()).bit);

    log();
    log("测试浮点数的差值");
    log();
    double a, b, c, d;

    // 最小规约正数
    c = std::numeric_limits<double>::min();
    // 最小规约正数的下一数
    d = std::nextafter(c, std::numeric_limits<double>::infinity());
    // 最大非规约正数
    b = std::nextafter(c, std::numeric_limits<double>::lowest());
    // 最大非规约正数的上一数
    a = std::nextafter(b, std::numeric_limits<double>::lowest());

    log(format("最大非规约正数       - 最大非规约正数的上一数: %.2000lf",
               b - a));
    log(format("最小规约正数         - 最大非规约正数:       : %.2000lf",
               c - b));
    log(format("最小规约正数的下一数 - 最小规约正数:         : %.2000lf",
               d - c));

    log();
    log("主进程正常退出");
    log();
    return 0;
}
