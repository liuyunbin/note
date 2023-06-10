
#include "test.h"

void test(const string& name, string bit) {
    bit = trim(bit);

    stringstream tmp(to_double_hand(bit));

    Node node;
    tmp >> node.x;

    string bit_cs = bitset<64>(node.y).to_string();

    cout << "        测试类型: " << name << endl;
    cout << "    测试的二进制: " << to_bit(bit) << endl;
    cout << "    存储的二进制: " << to_bit(bit_cs) << endl;
    cout << "          手动值: " << to_double_hand(bit) << endl;
    cout << "          存储值: " << to_double_cs(bit_cs) << "(精确值)";
    cout << setprecision(2) << fixed;
    cout << " --> " << node.x << "(保留两位小数)" << endl;
    cout << endl;
}

void test() {
    std::cout << "测试保留小数时的四舍六入五取偶" << std::endl << std::endl;

    cout << "        舍入方向: " << dict_round[fegetround()] << endl;
    test("测试保留小数时的 五进",
         "0 01111111100 0000000000000000000000000000000000000000000000000001");
    test("测试保留小数时的 五取偶(舍)",
         "0 01111111100 0000000000000000000000000000000000000000000000000000");
    test("测试保留小数时的 五取偶(入)",
         "0 01111111101 1000000000000000000000000000000000000000000000000000");
    return;
}

int main() {
    init();
    test();
    return 0;
}
