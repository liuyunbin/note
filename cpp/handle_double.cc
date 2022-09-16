//
// double 区分大小端
// 格式:    1-符号位 11-阶码(偏移量 1023) 52-尾码
// +0,-0             00000000000          全为0   非规约, 没有前置 1
// +1,-1             01111111111          全为0     规约,   有前置 1
// 无穷              11111111111          全为0   实际输出 -inf 或 inf
// 异常数字          11111111111        非全为0   实际输出 -nan 或 nan
// 非规约数          00000000000        非全为0   非规约, 没有前置 0
//
// 十进制数字   --> 二进制字符串  bitset<64>( 123 ).to_string()
// 二进制字符串 --> 十进制数字    bitset<64>("111").to_ulong()
//
// 为什么使用偏移量: 方便比较大小
//
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

union Node {
    double        val_double;
    unsigned long val_ulong;
};

map<int, string> dict; // 存储 2 的幂次

// 获取浮点数的二进制形式
string double_to_bit(const string& str) {
    stringstream input(str);
    Node node;
    input >> node.val_double;
    return bitset<64>(node.val_ulong).to_string();
}

// 两个相同的长度的数的加法
string add(const string& x, const string& y) {
    if (x.size() != y.size()) {
        // 非法
        cout << "参数非法" << x << "  " << y << endl;
        exit(-1);
    }

    int sum = 0;
    string z;

    for (int i = (int)x.size() - 1; i >= 0; --i) {
        sum += (x[i] - '0') + (y[i] - '0');
        z  = string(1, '0' + sum%10) + z;
        sum /= 10;
    }
    if (sum != 0) {
        z = string(1, '0' + sum) + z;
    }
    return z;
}

// 小数点前的整数的加法
string add_int(string x, string y) {
    if (x.size() > y.size()) {
        return add(y, x);
    }
    x = string(y.size() - x.size(), '0') + x;
    return add(x, y);
}

// 小数点后的数的加法
string add_double(string x, string y) {
    if (x.size() > y.size()) {
        return add_double(y, x);
    }
    x += string(y.size() - x.size(), '0');
    return add(x, y);
}

// 求 x * 2
// 表示小数点前的整数
string mul2(const string& str) {
    string z;
    int sum = 0;

    for (int i = (int)str.size() - 1; i >= 0; --i){
        sum += (str[i] - '0') * 2;
        z    = string(1, sum % 10 + '0') + z;
        sum /= 10;
    }
    if (sum != 0) {
        z = string(1, sum + '0') + z;
    }
    return z;
}

// 求 x / 2
// 表示小数点后的数
string div2(const string& str) {
    string z;
    int sum = 0;

    for (char ch : str){
        sum = sum * 10 + (ch - '0');
        z += string(1, sum / 2 + '0');
        sum %= 2;
    }
    if (sum != 0) {
        z += "5";
    }
    return z;
}

// 二进制的浮点数转化为 十进制,
// x --> 整数部分, y --> 小数部分
string bit_to_dec(const string& str_int, const string& str_dec) {
    string result_int = "0";
    for (int i = 0; i < (int)str_int.size(); ++i)
        if (str_int[i] == '1')
            result_int = add_int(result_int, dict[str_int.size() - 1 - i]);

    string result_dec;
    for (int i = 0; i < (int)str_dec.size(); ++i)
        if (str_dec[i] == '1')
            result_dec = add_double(result_dec, dict[- 1 - i]);

    if (result_dec.empty())
        return result_int;
    else
        return result_int + "." + result_dec;
}

// 人工: 二进制 double --> 十进制 double
string bit_to_double_by_hand(const string& str) {

    return str;
}

// 计算机: 二进制 double --> 十进制 double
string bit_to_double_by_cs(const string& str) {
    unsigned long x = bitset<64>(str).to_ulong();
    double y = *(double*)(&x); // 计算机实际的浮点数

    stringstream tmp;
    tmp << setprecision(2000) << fixed << y;
    string result = tmp.str();
    size_t index = result.find_last_not_of('0');

    if (result[index] == '.')
        --index;
    return result.substr(0, index + 1);
}

struct HandleDouble {
    string s_str;      // 符号位
    string e_str;      // 阶码
    int    e_int;      // 阶码的十进制
    int    e_int_real; // 去偏移后的十进制
    string f_str;      // 尾码
    string f_str_real; // 真实的尾码, 包括整数部分
    string type;       // 浮点数类型

    string arg;
    string result;

    void cal(const string& str) {
                   arg        = str;

                   s_str      = str.substr(0, 1);
                   e_str      = str.substr(1, 11);
        bitset<11> e_bit(e_str);
                   e_int      = e_bit.to_ulong();
                   e_int_real = e_int;

                   f_str      = str.substr(12);
                   f_str_real = f_str;
        bitset<52> f_bit(f_str);

        if (e_bit.all() && f_bit.none()) {
            // 阶码都为 1, 尾码都为 0
            // 正负无穷
            type  = s_str == "1" ? "负" : "正";
            type += "无穷";
        } else if (e_bit.all() && not f_bit.none()) {
            // 阶码都为 1, 尾码不都为 0
            // 非数字
            type = "非数字";
        } else if (e_bit.none() && f_bit.none()) {
            // 阶码都为 0, 尾码都为 0
            // 正负 0
            type  = s_str == "1" ? "负" : "正";
            type += "零";
        } else {
            string str_int;         // 尾码的整数部分
            string str_dec = f_str; // 尾码的小数部分

            if (e_bit.none() && not f_bit.none()) {
                // 阶码都为 0, 尾码不都为 0
                // 非规约数字
                type = "非规约数字";
                f_str_real = "0." + f_str;
                f_str_real = f_str;
                e_int_real = e_int - 1022;
            } else {
                // 阶码不都为 0, 也不都为 1
                // 规约数字
                type = "规约数字";
                f_str_real = "1." + f_str;
                e_int_real = e_int - 1023;
                str_int = "1";
            }

            // 处理 阶码 的移位
            if (e_int_real > 0) {
                if ((int)str_dec.size() < e_int_real) {
                    str_dec += string(e_int_real - str_dec.size(), 0);
                }

                str_int += str_dec.substr(0, e_int_real);
                str_dec  = str_dec.substr(e_int_real);
            } else if (e_int_real < 0) {
                if (!str_int.empty()) {
                    str_dec = string(-e_int_real - 1 , '0') + str_int +  str_dec;
                } else {
                    str_dec = string(-e_int_real , '0') +  str_dec;
                }
                str_int = "";
            }
            result = bit_to_dec(str_int, str_dec);
            if (s_str == "1") {
                result = "-" + result;
            }
        }
    }

    void output() {
        cout << "                类型: " << type       << endl;
        cout << "              符号位: " << s_str      << endl;
        cout << "                阶码: " << e_str      << endl;
        cout << "          十进制阶码: " << e_int      << endl;
        cout << "    真实的十进制阶码: " << e_int_real << endl;
        cout << "                尾码: " << f_str      << endl;
        cout << "          真实的尾码: " << f_str_real << endl;
        cout << "      二进制完整格式: " << arg        << endl;
        cout << "计算机实际存储的小数: " << bit_to_double_by_cs(arg) << endl;
        cout << "        手动计算结果: " << result     << endl;
    }
};

void handle_bit(const string& str) {
    string str_format(64, '0');
    for (size_t  i = 0, k = 0; i < str.size() && k < 64; ++i) {
        if (str[i] == ' ' || str[i] == '\t')
            continue;
        if (str[i] != '0' && str[i] != '1') {
            cout << str[i] << " 非法" << endl;
            return ;
        }
        str_format[k++] = str[i];
    }
    HandleDouble t;
    t.cal(str_format);
    t.output();
}

void handle_double(const string& str) {
    handle_bit(double_to_bit(str));
}

int main() {
    int n = 3000;
    string str = "5";
    for (int  i = -1; i >= -n; --i) {
        dict[i] = str;
        str = div2(str);
        str = "1";
        for (int i = 0; i <= n; ++i) {
            dict[i] = str;
            str = mul2(str);
        }
        for (;;) {
            system("clear");
            cout << "本程序用于查看浮点数的存储和四舍五入:"    << endl;
            cout << "    如果输入的是二进制:"                  << endl;
            cout << "        将自动忽略行内空格"               << endl;
            cout << "        不足 64 位将用 0 补齐"            << endl;
            cout << "        超过 64 位的部分将忽略"           << endl;
            cout << "        请确保前 64 位只包含 0 或 1"      << endl;
            cout << "    如果输入的是浮点数. 请确保包含小数点" << endl;
            cout << endl;
            cout << "        请输入浮点数: ";

            getline(cin, str);

            if (str.find_first_of('.') != std::string::npos) {
                // 浮点数
                handle_double(str);
            } else {
                // 二进制
                handle_bit(str);
            }
            cout << endl << "输入回车继续";
            getchar();
        }
    }
    return 0;
}

