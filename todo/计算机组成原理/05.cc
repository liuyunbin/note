
#include "test.h"

// type 为 0 表示除, 为 1 表示 乘, 2 表示小于, 3 表示使用 isless, 其他使用 lrint
void test(const string& name, double x, double y, int type = 0) {
    feclearexcept(FE_ALL_EXCEPT);
    string result;
    if (type == 0)
        result = x / y ? "true" : "false";
    else if (type == 1)
        result = x * y ? "true" : "false";
    else if (type == 2)
        result = x < y ? "true" : "false";
    else if (type == 3)
        result = isless(x, y) ? "true" : "false";
    else
        result = lrint(x) ? "true" : "false";

    string except;
    for (auto v : dict_except)
        if (fetestexcept(v.first)) {
            except += v.second + " ";
        }

    if (except.empty()) except = "空";
    cout << endl;
    cout << "测试类型: " << name << endl;
    cout << "测试结果: " << result << endl;
    cout << "异常信息: " << except << endl;
}

void test() {
    double x;
    cout << "测试浮点数的异常" << endl;
    test("测试除以零", 1, 0.0);
    test("测试结果不准确", 1, 10.0);
    x = numeric_limits<double>::max();
    test("测试上溢", x, 2, 1);
    x = numeric_limits<double>::denorm_min();
    test("测试下溢", x, 2);

    test("测试 NAN < NAN", NAN, NAN, 2);
    test("测试 isless(NAN, NAN)", NAN, NAN, 3);
    test("测试 lrint(NAN)", NAN, NAN, 4);

    x = numeric_limits<double>::quiet_NaN();
    test("测试 quiet_NAN < quiet_NAN", x, x, 2);
    test("测试 isless(quiet_NAN, quiet_NAN)", x, x, 3);
    test("测试 lrint(quiet_NAN)", x, x, 4);

    x = numeric_limits<double>::signaling_NaN();
    test("测试 signaling_NaN < signaling_NaN", x, x, 2);
    test("测试 isless(signaling_NaN, signaling_NaN)", x, x, 3);
    test("测试 lrint(signaling_NaN)", x, x, 4);
}

int main() {
    init();
    test();
    return 0;
}
