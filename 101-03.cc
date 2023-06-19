
#include "log.h"

void test(const std::string& name, const std::string& bit) {
    Double d(bit);

    log();
    log("        测试类型: " + name);
    log("    测试的二进制: " + d.bit_by_test);
    log("    存储的二进制: " + d.bit_by_cs);
    log("          手动值: " + d.double_by_hand);
    log("          存储值: " + d.double_by_cs);
    log("    保留两位小数: " + to_string("%.2lf", d.data));
}

void test() {
    log();
    log("测试保留小数时的四舍六入五取偶");
    log();
    log("        舍入方向: " + dict_round[fegetround()]);
    test("测试保留小数时的 五进",
         "0 01111111100 0000000000000000000000000000000000000000000000000001");
    test("测试保留小数时的 五取偶(舍)",
         "0 01111111100 0000000000000000000000000000000000000000000000000000");
    test("测试保留小数时的 五取偶(入)",
         "0 01111111101 1000000000000000000000000000000000000000000000000000");
    log();
}

int main() {
    init();
    test();
    return 0;
}
