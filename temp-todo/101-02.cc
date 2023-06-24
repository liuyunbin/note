
#include "log.h"

void test(const std::string& str, int x, int y) {
    log();
    log("测试: ", str, ", 求商: ", x / y, ", 求余: ", x % y);
    log();
}

int main() {
    log();
    log("测试整数溢出以及除法的符号");
    log();

    int x = std::numeric_limits<int>::max();
    log("测试有符号整数max      : ", x);
    x = x + 10;
    log("测试有符号整数max + 10 : ", x);

    unsigned y = std::numeric_limits<unsigned int>::max();
    log("测试无符号整数max      : ", y);
    y = y + 10;
    log("测试无符号整数max + 10 : ", y);

    test("5/2", 5, 2);
    test("5/-2", 5, -2);
    test("-5/2", -5, 2);
    test("-5/-2", -5, -2);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
