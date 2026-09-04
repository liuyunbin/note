
#include "log.h"

// type 为 0 表示除, 为 1 表示 乘, 2 表示小于, 3 表示使用 isless, 其他使用 lrint
void test(const std::string& name, double x, double y, int type = 0) {
    std::feclearexcept(FE_ALL_EXCEPT);
    std::string result;
    if (type == 0)
        x = x / y;
    else if (type == 1)
        x = x * y;
    else if (type == 2)
        result = x < y ? "true" : "false";
    else if (type == 3)
        result = std::isless(x, y) ? "true" : "false";
    else
        result = std::lrint(x) ? "true" : "false";

    std::string except;
    for (auto v : dict_except)
        if (std::fetestexcept(v.first)) {
            except += v.second + " ";
        }

    if (except.empty()) {
        except = "空";
    }

    log();
    log("测试类型: " + name);
    log("测试结果: " + result);
    log("异常信息: " + except);
}

int main() {
    log();
    log("测试浮点数的异常");
    log();

    double x;
    test("测试除以零", 1, 0.0);
    test("测试结果不准确", 1, 10.0);
    x = std::numeric_limits<double>::max();
    test("测试上溢", x, 2, 1);
    x = std::numeric_limits<double>::denorm_min();
    test("测试下溢", x, 2);

    test("测试 NAN < NAN", NAN, NAN, 2);
    test("测试 isless(NAN, NAN)", NAN, NAN, 3);
    test("测试 lrint(NAN)", NAN, NAN, 4);

    x = std::numeric_limits<double>::quiet_NaN();
    test("测试 quiet_NAN < quiet_NAN", x, x, 2);
    test("测试 isless(quiet_NAN, quiet_NAN)", x, x, 3);
    test("测试 lrint(quiet_NAN)", x, x, 4);

    x = std::numeric_limits<double>::signaling_NaN();
    test("测试 signaling_NaN < signaling_NaN", x, x, 2);
    test("测试 isless(signaling_NaN, signaling_NaN)", x, x, 3);
    test("测试 lrint(signaling_NaN)", x, x, 4);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
