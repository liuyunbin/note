
#include "test.h"

template <typename T>
void test(const string& name, T bit) {
    cout << endl;
    cout << "测试类型: " << name << endl;
    cout << "  二进制: " << to_bit(bit) << endl;
    cout << "  计算机: " << to_double_cs(bit) << endl;
    cout << "    手动: " << to_double_hand(bit) << endl;
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
    std::cout << to_bit(numeric_limits<double>::lowest()) << std::endl;
    std::cout << "最小非规约正数: ";
    std::cout << to_bit(numeric_limits<double>::denorm_min()) << std::endl;
    std::cout << "最小  规约正数: ";
    std::cout << to_bit(numeric_limits<double>::min()) << std::endl;
    std::cout << "最大  规约正数: ";
    std::cout << to_bit(numeric_limits<double>::max()) << std::endl;
    std::cout << "        正无穷: ";
    std::cout << to_bit(numeric_limits<double>::infinity()) << std::endl;

    std::cout << std::endl << "测试浮点数的差值" << std::endl;
    double a, b, c, d;

    // 最小规约正数
    c = numeric_limits<double>::min();
    // 最小规约正数的下一数
    d = nextafter(c, numeric_limits<double>::infinity());
    // 最大非规约正数
    b = nextafter(c, numeric_limits<double>::lowest());
    // 最大非规约正数的上一数
    a = nextafter(b, numeric_limits<double>::lowest());

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
