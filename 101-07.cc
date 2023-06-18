
#include "log.h"

template <typename T>
void test(const std::string& name, T bit) {
    Double d(bit);

    log();
    log("测试类型: " + name);
    log("  二进制: " + d.bit);
    log("  计算机: " + d.double_by_cs);
    log("    手动: " + d.double_by_hand);
}

void test() {
    test("正零",
         "0 00000000000 0000000000000000000000000000000000000000000000000000");
    test("最小非规约正数",
         "0 00000000000 0000000000000000000000000000000000000000000000000001");
    test("最大非规约正数",
         "0 00000000000 1111111111111111111111111111111111111111111111111111");
    test("最小  规约正数",
         "0 00000000001 0000000000000000000000000000000000000000000000000000");
    test("最大  规约正数",
         "0 11111111110 1111111111111111111111111111111111111111111111111111");
    test("正无穷",
         "0 11111111111 0000000000000000000000000000000000000000000000000000");
    test("非数字",
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
    double a, b, c, d;

    // 最小规约正数
    c = std::numeric_limits<double>::min();
    // 最小规约正数的下一数
    d = std::nextafter(c, std::numeric_limits<double>::infinity());
    // 最大非规约正数
    b = std::nextafter(c, std::numeric_limits<double>::lowest());
    // 最大非规约正数的上一数
    a = std::nextafter(b, std::numeric_limits<double>::lowest());

    log("最大非规约正数       - 最大非规约正数的上一数: " +
        std::to_string(b - a));
    log("最小规约正数         - 最大非规约正数:         " +
        std::to_string(c - b));
    log("最小规约正数的下一数 - 最小规约正数:           " +
        std::to_string(d - c));
    log();
}

int main() {
    init();
    test();
    return 0;
}
