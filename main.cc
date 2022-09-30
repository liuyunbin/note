
#include <cfenv>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <string>

using namespace std;

// type 为 0 测试 小于号
// type 为 1 测试 isless
void test_except(const string& name,  double x, double y, int type) {
    map<int, string> dict; // 存储浮点数异常
    dict[FE_DIVBYZERO] = "除以 0";
    dict[FE_INEXACT] = "结果不准确";
    dict[FE_INVALID] = "参数非法";
    dict[FE_OVERFLOW] = "上溢";
    dict[FE_UNDERFLOW] = "下溢";

    feclearexcept(FE_ALL_EXCEPT);
    string result;
    if (type == 0) {
        result = x < y ? "true" : "false";
    } else {
        result = isless(x, y) ? "true" : "false";
    }

    string except;
    for (auto v : dict)
        if (fetestexcept(v.first))
            except += v.second + " ";

    if (except.empty())
        except = "空";
    cout << "测试类型: " << name << endl;
    cout << "测试结果: " << result << endl;
    cout << "异常信息: " << except << endl;
    cout << endl;
}

int main() {
    double x;

    x = NAN;
    test_except("测试 NAN < NAN", x, x, 0);
    test_except("测试 isless(NAN, NAN)", x, x, 1);

    x = numeric_limits<double>::quiet_NaN();
    test_except("测试 quiet_NAN < quiet_NAN", x, x, 0);
    test_except("测试 isless(quiet_NAN, quiet_NAN)", x, x, 1);

    x = numeric_limits<double>::signaling_NaN();
    test_except("测试 signaling_NaN < signaling_NaN", x, x, 0);
    test_except("测试 isless(signaling_NaN, signaling_NaN)", x, x, 1);

    return 0;
}

