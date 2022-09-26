
// 浮点数区分大小端
//
// 格式:
// *  float: 1-符号位  8-阶码(偏移量  127) 23-尾码
// * double: 1-符号位 11-阶码(偏移量 1023) 52-尾码
//
// 类型:
// * 正负  零(FP_ZERO)     : 阶码都为 0, 尾码  都为 0
// * 正负无穷(FP_INFINITE) : 阶码都为 1, 尾码  都为 0, inf
// *   非数字(FP_NAN)      : 阶码都为 1, 尾码不都为 0, nan
// *   规约数(FP_NORMAL)   : 阶码都为 0, 尾码不都为 1, 尾码整数部分为 0
// * 非规约数(FP_SUBNORMAL): 阶码不都为 0 或 1,        尾码整数部分为 1
// * 查看浮点数类型        : pclassify(...)
//
// 舍入模式:
// * 向下舍入(FE_DOWNWARD)  : std::floor
// * 向上舍入(FE_UPWARD)    : std::ceil
// * 向零舍入(FE_TOWARDZERO): std::trunc, 浮点数-->整数
// * 最近舍入(FE_TONEAREST) :  默认舍入模式, 四舍六入五取偶
// * 四舍五入               : std::round
// * 由舍入模式决定         : std::rint, std::nearbyint, printf, 浮点数的存储 等
// * 查看舍入模式           : fegetround()
// * 设置舍入模式           : fesetround(...)
//
// 浮点数异常:
// * 除以 0      : FE_DIVBYZERO
// * 结果不准确  : FE_INEXACT
// * 参数非法    : FE_INVALID
// * 上溢        : FE_OVERFLOW
// * 下溢        : FE_UNDERFLOW
// 清空浮点数异常: feclearexcept(FE_ALL_EXCEPT);
// 测试浮点数异常: fetestexcept(...);
//
// 浮点数字符串 --> 浮点数二进制, 可能会损失精度
// 浮点数二进制 --> 浮点数字符串,   不会损失精度
//
// 十进制数字   --> 二进制字符串, 可能有精度损失, bitset<64>( 123 ).to_string()
// 二进制字符串 --> 十进制数字,   不会有精度损失, bitset<64>("111").to_ulong()
//
// 为什么使用偏移量: 方便比较大小
// 相邻可表示的浮点数的差值是不是一定的: 不是
// TODO: 16 位精度究竟是什么意思?

#include <ctype.h>

#include <algorithm>
#include <bitset>
#include <cfenv>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 存储 2 的幂次
// 2 的 10 次 1024
// 2 的  0 次 1
// 2 的 -1 次 5
// 2 的 -2 次 25
map<int, string> dict;
void init_dict(int n) {
    string str;

    str = "5";
    for (int i = -1; i >= -n; --i) {
        dict[i] = str;

        str = "";
        int sum = 0;
        for (char ch : dict[i]) {
            sum = sum * 10 + (ch - '0');
            str += string(1, sum / 2 + '0');
            sum %= 2;
        }
        if (sum != 0) str += "5";
    }

    str = "1";
    for (int i = 0; i <= n; ++i) {
        dict[i] = str;

        str = "";
        int sum = 0;
        for (int j = (int)dict[i].size() - 1; j >= 0; --j) {
            sum += (dict[i][j] - '0') * 2;
            str = string(1, sum % 10 + '0') + str;
            sum /= 10;
        }
        if (sum != 0) str = string(1, sum + '0') + str;
    }
}

// 手动计算的结果
// 两个数的加法
// type 为 0 表示整数加法 1 表示小数加法
string add(string x, string y, int type = 0) {
    if (x.size() > y.size()) swap(x, y);

    if (type == 0)
        x = string(y.size() - x.size(), '0') + x; // 整数
    else
        x = x + string(y.size() - x.size(), '0'); // 小数

    int sum = 0;
    string z;

    for (int i = (int)x.size() - 1; i >= 0; --i) {
        sum += (x[i] - '0') + (y[i] - '0');
        z = string(1, '0' + sum % 10) + z;
        sum /= 10;
    }
    if (sum != 0) z = string(1, '0' + sum) + z;
    return z;
}

// 二进制的浮点数转化为 十进制,
// str_int --> 整数部分, str_dec --> 小数部分
string bit_to_double(const string& str_int, const string& str_dec) {
    string result_int = "0";
    for (int i = 0; i < (int)str_int.size(); ++i)
        if (str_int[i] == '1')
            result_int = add(result_int, dict[str_int.size() - 1 - i]);

    string result_dec;
    for (int i = 0; i < (int)str_dec.size(); ++i)
        if (str_dec[i] == '1') result_dec = add(result_dec, dict[-1 - i], 1);

    if (result_dec.empty())
        return result_int;
    else
        return result_int + "." + result_dec;
}

// 二进制的浮点数转化为 十进制
string bit_to_double(const string& str) {
    string s_str = str.substr(0, 1);
    string e_str = str.substr(1, 11);
    string f_str = str.substr(12);

    bitset<11> e_bit(e_str);
    int e_int = e_bit.to_ulong();

    bitset<52> f_bit(f_str);

    // 阶码都为 1, 尾码都为 0
    if (e_bit.all() && f_bit.none()) return s_str == "1" ? "负无穷" : "正无穷";

    // 阶码都为 1, 尾码不都为 0
    if (e_bit.all() && not f_bit.none()) return "非数字";

    // 阶码都为 0, 尾码都为 0
    if (e_bit.none() && f_bit.none()) return s_str == "1" ? "负零" : "正零";

    string str_int;          // 尾码的整数部分
    string str_dec = f_str;  // 尾码的小数部分

    if (e_bit.none() && not f_bit.none()) {
        // 阶码都为 0, 尾码不都为 0
        // 非规约数字
        f_str = "0." + f_str;
        e_int -= 1022;
    } else {
        // 阶码不都为 0, 也不都为 1
        // 规约数字
        f_str = "1." + f_str;
        e_int -= 1023;
        str_int = "1";
    }

    // 处理 阶码 的移位
    if (e_int > 0) {
        if ((int)str_dec.size() < e_int)
            str_dec += string(e_int - str_dec.size(), 0);

        str_int += str_dec.substr(0, e_int);
        str_dec = str_dec.substr(e_int);
    } else if (e_int < 0) {
        if (!str_int.empty())
            str_dec = string(-e_int - 1, '0') + str_int + str_dec;
        else
            str_dec = string(-e_int, '0') + str_dec;
        str_int = "";
    }
    string result = bit_to_double(str_int, str_dec);
    if (s_str == "1")
        result = "-" + result;
    return result;
}

// 移除所有的 空字符
string trim(const string& str) {
    string result;
    for (char ch : str)
        if (!isspace(ch)) result += ch;
    return result;
}

string bit_to_string(string str) {
    str = trim(str);
    if ((int)str.size() < 64)
        str = str + string(64 - (int)str.size(), '0');

    string s_str = str.substr(0, 1);
    string e_str = str.substr(1, 11);
    string f_str = str.substr(12, 52);
    string left;
    if (str.size() > 64) left = str.substr(64);

    bitset<11> e_bit(e_str);
    bitset<52> f_bit(f_str);

    int e_int = e_bit.to_ulong();

    if (e_bit.none() && not f_bit.none())
        // 非规约数字: 阶码都为 0, 尾码不都为 0
        e_int -= 1022;
    else if (not e_bit.all() && not e_bit.none())
        // 规约数字: 阶码不都为 0, 也不都为 1
        e_int -= 1023;

    return s_str + " " + e_str + "(" + to_string(e_int) + ") " + f_str + " " + left;
}

// 计算机计算的结果
union Node {
    double x;
    uint64_t y;
    char s[8];

    string to_str() {
        stringstream tmp;
        tmp << setprecision(2000) << fixed << x;  // TODO: 两千够吗?
        string result = tmp.str();
        size_t index = result.find_last_not_of('0');

        if (result[index] == '.') --index;
        return result.substr(0, index + 1);
    }

    string to_bit() { return bit_to_string(bitset<64>(y).to_string()); }

    // 计算机 实际存储
    string get_mem() {
        string result;
        for (int i = 0; i < 8; ++i)
            result += bitset<8>((unsigned char)s[i]).to_string() + " ";
        return result;
    }
};

// 测试舍入模式
// bit 为 二进制
void test_round(const string& name, string bit) {
    bit = trim(bit);
    if ((int)bit.size() < 64)
        bit += string(64 - (int)bit.size(), '0');

    Node node;

    string str = bit_to_double(bit);

    stringstream tmp(str);
    tmp >> node.x;

    cout << endl;
    cout << "    测试类型: " << name << endl;
    cout << "测试的二进制: " << bit_to_string(bit) << endl;
    cout << "存储的二进制: " << node.to_bit() << endl;
    cout << "      手动值: " << str << endl;
    cout << "      存储值: " << node.to_str() << "(精确值)";
    cout << setprecision(2)  << fixed;
    cout << " --> " << node.x << "(保留两位小数)" << endl;
}

void test_round(const string& name, double x) {
    Node node;
    node.x = x;
    test_round(name, bitset<64>(node.y).to_string());
}

// 测试存储
void test(const string& name, double v) {
    Node n;
    n.x = v;
    cout << name << ": " << n.to_bit() << endl;
}

// 获取浮点数异常
string get_double_except() {
    map<int, string> m;
    m[FE_DIVBYZERO] = "除以 0";
    m[FE_INEXACT] = "结果不准确";
    m[FE_INVALID] = "参数非法";
    m[FE_OVERFLOW] = "上溢";
    m[FE_UNDERFLOW] = "下溢";

    string result;
    for (auto v : m)
        if (fetestexcept(v.first)) result += v.second + " ";
    return result;
}

#define TEST_DOUBLE_EXCEPT(name, y) \
    feclearexcept(FE_ALL_EXCEPT); \
    cout << name << "(" << y << "): ";\
    cout << get_double_except() << endl;

int main() {
    init_dict(2000);

    map<int, string> m;
    m[FE_DOWNWARD] = "向下舍入";
    m[FE_TONEAREST] = "最近舍入";
    m[FE_TOWARDZERO] = "向零舍入";
    m[FE_UPWARD] = "向上舍入";

    //fesetround(FE_TOWARDZERO);
    cout << "    舍入方向: " << m[fegetround()] << endl;

    test_round("测试保留小数时的 五取偶(舍)", 0.125);
    test_round("测试保留小数时的 五取偶(入)", 0.375);
    test_round("测试存储小数时的 五取偶(舍)",
            "0 10000110011 0000 00000000 00000000 00000000 00000000 00000000 00000000 1");
    test_round("测试存储小数时的 五取偶(入)",
            "0 10000110011 0000 00000000 00000000 00000000 00000000 00000000 00000001 1");

    // digits10
    // 能无更改地表示的十进制位数
    cout << endl;
    test("      最小  规约正数", numeric_limits<double>::min());
    test("      最大  规约正数", numeric_limits<double>::max());
    test("      最小  规约负数", numeric_limits<double>::lowest());
    test("      最小非规约正数", numeric_limits<double>::denorm_min());
    test("              正无穷", numeric_limits<double>::infinity());
    test("      有异常的非数字", numeric_limits<double>::quiet_NaN());
    test("      无异常的非数字", numeric_limits<double>::signaling_NaN());
    test("下个可表示的数 - 1.0", numeric_limits<double>::epsilon());
    test("结果与上一条应该相同", nextafter(1.0, numeric_limits<double>::infinity()) - 1.0);

    double x = 1;
    cout << endl << "测试浮点数的异常" << endl;
    TEST_DOUBLE_EXCEPT("测试 1/0.0", x/0.0);
    TEST_DOUBLE_EXCEPT("测试 1/10.0", x/10.0);
    x = numeric_limits<double>::quiet_NaN();
    TEST_DOUBLE_EXCEPT("测试 quiet_NaN/10.0", x/10.0);
    x = numeric_limits<double>::signaling_NaN();
    TEST_DOUBLE_EXCEPT("测试 signaling_NaN/10.0", x/10.0);
    x = numeric_limits<double>::max();
    TEST_DOUBLE_EXCEPT("测试 最大  规约数 * 2", x * 2);
    x = numeric_limits<double>::denorm_min();
    TEST_DOUBLE_EXCEPT("测试 最小正非规约数 / 2", x / 2);

    return 0;
}
