
#include "log.h"

#include "101-00.h"

void test(const std::string& name, const std::string& bit) {
    Double d(bit);

    std::cout << "        测试类型: " << name << std::endl;
    std::cout << "    测试的二进制: " << d.bit_by_test << std::endl;
    std::cout << "    存储的二进制: " << d.bit_by_cs << std::endl;
    std::cout << "          手动值: " << d.double_by_hand << std::endl;
    std::cout << "          存储值: " << d.double_by_cs << "(精确值)";
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << " --> " << d.data << "(保留两位小数)" << std::endl;
    std::cout << std::endl;
}

void test() {
    std::cout << "测试保留小数时的四舍六入五取偶" << std::endl << std::endl;

    std::cout << "        舍入方向: " << dict_round[fegetround()] << std::endl;
    test("测试保留小数时的 五进",
         "0 01111111100 0000000000000000000000000000000000000000000000000001");
    test("测试保留小数时的 五取偶(舍)",
         "0 01111111100 0000000000000000000000000000000000000000000000000000");
    test("测试保留小数时的 五取偶(入)",
         "0 01111111101 1000000000000000000000000000000000000000000000000000");
}

int main() {
    init();
    test();
    return 0;
}
