
#include <cctype>
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

using namespace std;

map<int, string> dict_pow;    // 存储 2 的幂次
                              // 负幂次只存储小数点后的部分
map<int, string> dict_except; // 存储浮点数异常
map<int, string> dict_round;  // 存储舍入模式

void init();

union Node {
    double x;
    uint64_t y;
};

// 移除所有的 空字符
string trim(const string& str);

string to_double_hand(const string& bit);
string to_double_cs(const string& bit);
string to_bit(const string& bit);

// 测试舍入模式
// bit 为 二进制
void test_round(const string& name, string bit) {
    bit = trim(bit);
    if ((int)bit.size() < 64)
        bit += string(64 - (int)bit.size(), '0');

    stringstream tmp(to_double_hand(bit));

    Node node;
    tmp >> node.x;

    string bit_cs = bitset<64>(node.y).to_string();

    cout << endl;
    cout << "    测试类型: " << name << endl;
    cout << "测试的二进制: " << to_bit(bit) << endl;
    cout << "存储的二进制: " << to_bit(bit_cs) << endl;
    cout << "      手动值: " << to_double_hand(bit) << endl;
    cout << "      存储值: " << to_double_cs(bit_cs) << "(精确值)";
    cout << setprecision(2)  << fixed;
    cout << " --> " << node.x << "(保留两位小数)" << endl;
}

void test_round(const string& name, double x) {
    Node node;
    node.x = x;
    test_round(name, bitset<64>(node.y).to_string());
}

void test_round() {
    cout << "    舍入方向: " << dict_round[fegetround()] << endl;
    test_round("测试保留小数时的 五取偶(舍)", 0.125);
    test_round("测试保留小数时的 五取偶(入)", 0.375);
    test_round("测试存储小数时的 五取偶(舍)",
            "0 10000110011 0000 00000000 00000000 00000000 00000000 00000000 00000000 1");
    test_round("测试存储小数时的 五取偶(入)",
            "0 10000110011 0000 00000000 00000000 00000000 00000000 00000000 00000001 1");
}

// 测试存储
//void test(const string& name, double v) {
//    Node n;
//    n.x = v;
//    cout << name << ": " << n.to_bit() << endl;
//}

// 获取浮点数异常
string get_double_except() {
    string result;
    for (auto v : dict_except)
        if (fetestexcept(v.first)) result += v.second + " ";
    return result;
}

#define TEST_DOUBLE_EXCEPT(name, y) \
    feclearexcept(FE_ALL_EXCEPT); \
    cout << name << "(" << y << "): ";\
    cout << get_double_except() << endl;

int main() {
    init();
    test_round(); // 测试 舍入模式

    return 0;
    // digits10
    // 能无更改地表示的十进制位数
//    cout << endl;
//    test("      最小  规约正数", numeric_limits<double>::min());
//    test("      最大  规约正数", numeric_limits<double>::max());
//    test("      最小  规约负数", numeric_limits<double>::lowest());
//    test("      最小非规约正数", numeric_limits<double>::denorm_min());
//    test("              正无穷", numeric_limits<double>::infinity());
//    test("      有异常的非数字", numeric_limits<double>::quiet_NaN());
//    test("      无异常的非数字", numeric_limits<double>::signaling_NaN());
//    test("下个可表示的数 - 1.0", numeric_limits<double>::epsilon());
//    test("结果与上一条应该相同", nextafter(1.0, numeric_limits<double>::infinity()) - 1.0);
//
//    double x = 1;
//    cout << endl << "测试浮点数的异常" << endl;
//    TEST_DOUBLE_EXCEPT("测试 1/0.0", x/0.0);
//    TEST_DOUBLE_EXCEPT("测试 1/10.0", x/10.0);
//    x = numeric_limits<double>::quiet_NaN();
//    TEST_DOUBLE_EXCEPT("测试 quiet_NaN/10.0", x/10.0);
//    x = numeric_limits<double>::signaling_NaN();
//    TEST_DOUBLE_EXCEPT("测试 signaling_NaN/10.0", x/10.0);
//    x = numeric_limits<double>::max();
//    TEST_DOUBLE_EXCEPT("测试 最大  规约数 * 2", x * 2);
//    x = numeric_limits<double>::denorm_min();
//    TEST_DOUBLE_EXCEPT("测试 最小正非规约数 / 2", x / 2);
//
//    return 0;
}

// 移除所有的 空字符
string trim(const string& str) {
    string result;
    for (char ch : str)
        if (!isspace(ch)) result += ch;
    return result;
}

void init() {
    // 浮点数异常
    dict_except[FE_DIVBYZERO] = "除以 0";
    dict_except[FE_INEXACT] = "结果不准确";
    dict_except[FE_INVALID] = "参数非法";
    dict_except[FE_OVERFLOW] = "上溢";
    dict_except[FE_UNDERFLOW] = "下溢";

    // 舍入方向
    dict_round[FE_DOWNWARD] = "向下舍入";
    dict_round[FE_TONEAREST] = "最近舍入";
    dict_round[FE_TOWARDZERO] = "向零舍入";
    dict_round[FE_UPWARD] = "向上舍入";

    // 2 的幂次
    int n = 2000;
    string str;

    str = "5";
    for (int i = -1; i >= -n; --i) {
        dict_pow[i] = str;

        str = "";
        int sum = 0;
        for (char ch : dict_pow[i]) {
            sum = sum * 10 + (ch - '0');
            str += string(1, sum / 2 + '0');
            sum %= 2;
        }
        if (sum != 0) str += "5";
    }

    str = "1";
    for (int i = 0; i <= n; ++i) {
        dict_pow[i] = str;

        str = "";
        int sum = 0;
        for (int j = (int)dict_pow[i].size() - 1; j >= 0; --j) {
            sum += (dict_pow[i][j] - '0') * 2;
            str = string(1, sum % 10 + '0') + str;
            sum /= 10;
        }
        if (sum != 0) str = string(1, sum + '0') + str;
    }
}

string to_double_cs(const string& bit) {
    Node node;
    node.y = bitset<64>(bit.substr(0, 64)).to_ulong();
    stringstream tmp;
    tmp << setprecision(2000) << fixed << node.x;  // TODO: 两千够吗?
    string result = tmp.str();
    size_t index = result.find_last_not_of('0');

    if (result[index] == '.') --index;
    return result.substr(0, index + 1);
}

string to_bit(const string& bit) {
    string s_str = bit.substr(0, 1);
    string e_str = bit.substr(1, 11);
    string f_str = bit.substr(12, 52);
    string other;
    if (bit.size() > 64) other = bit.substr(64);

    bitset<11> e_bit(e_str);
    bitset<52> f_bit(f_str);

    int e_int = e_bit.to_ulong();

    if (e_bit.none() && not f_bit.none())
        // 非规约数字: 阶码都为 0, 尾码不都为 0
        e_int -= 1022;
    else if (not e_bit.all() && not e_bit.none())
        // 规约数字: 阶码不都为 0, 也不都为 1
        e_int -= 1023;

    return s_str + " " + e_str + "(" + to_string(e_int) + ") " + f_str + " " + other;
}

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
string to_double_hand(const string& str_int, const string& str_dec) {
    string result_int = "0";
    for (int i = 0; i < (int)str_int.size(); ++i)
        if (str_int[i] == '1')
            result_int = add(result_int, dict_pow[str_int.size() - 1 - i]);

    string result_dec;
    for (int i = 0; i < (int)str_dec.size(); ++i)
        if (str_dec[i] == '1') result_dec = add(result_dec, dict_pow[-1 - i], 1);

    if (result_dec.empty())
        return result_int;
    else
        return result_int + "." + result_dec;
}

// 二进制的浮点数转化为 十进制
string to_double_hand(const string& str) {
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
    string result = to_double_hand(str_int, str_dec);
    if (s_str == "1")
        result = "-" + result;
    return result;
}

