
#include "log.h"

template <typename T>
void test(const std::string& name, T bit) {
    Double d(bit);

    std::cout << std::endl;
    std::cout << "测试类型: " << name << std::endl;
    std::cout << "  二进制: " << d.bit << std::endl;
    std::cout << "  计算机: " << d.double_by_cs << std::endl;
    std::cout << "    手动: " << d.double_by_hand << std::endl;
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

    std::cout << std::endl << "使用 numeric_limits" << std::endl;
    std::cout << "最小非规约负数: ";
    std::cout << Double(std::numeric_limits<double>::lowest()).bit << std::endl;
    std::cout << "最小非规约正数: ";
    std::cout << Double(std::numeric_limits<double>::denorm_min()).bit
              << std::endl;
    std::cout << "最小  规约正数: ";
    std::cout << Double(std::numeric_limits<double>::min()).bit << std::endl;
    std::cout << "最大  规约正数: ";
    std::cout << Double(std::numeric_limits<double>::max()).bit << std::endl;
    std::cout << "        正无穷: ";
    std::cout << Double(std::numeric_limits<double>::infinity()).bit
              << std::endl;

    std::cout << std::endl << "测试浮点数的差值" << std::endl;
    double a, b, c, d;

    // 最小规约正数
    c = std::numeric_limits<double>::min();
    // 最小规约正数的下一数
    d = std::nextafter(c, std::numeric_limits<double>::infinity());
    // 最大非规约正数
    b = std::nextafter(c, std::numeric_limits<double>::lowest());
    // 最大非规约正数的上一数
    a = std::nextafter(b, std::numeric_limits<double>::lowest());

    std::cout << "最大非规约正数       - 最大非规约正数的上一数: ";
    std::cout << b - a << std::endl;

    std::cout << "最小规约正数         - 最大非规约正数:         ";
    std::cout << c - b << std::endl;

    std::cout << "最小规约正数的下一数 - 最小规约正数:           ";
    std::cout << d - c << std::endl;
}

int main() {
    init();
    test();
    return 0;
}
