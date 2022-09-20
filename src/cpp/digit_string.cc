//
// 原码: 正数: 最高位添加 0, 负数: 最高位添加 1
// 反码: 正数: 等于原码, 负数: 在原码的基础上, 除符号位外, 各位取反
// 补码: 正数: 等于原码, 负数: 在反码的基础上, 加 1
// 移码: 加上指定数字, 使其全部变正
//
// int (假设 32 位)
// int (假设 32 位)
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
#include <ctype.h>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

// 忽略所有的空白字符 并格式化
// 返回结果: 空字符串, 零(+0), 正数(+1), 负数(-1)
string digit_string_check_and_format(const string &str) {
    string result;
    // 去掉所有的空白字符
    for (char ch : str)
        if (not isspace(ch))
            result.push_back(ch);

    if (result == "")
        return "";

    if (result[0] != '-') {
        result = "+" + result;
    }

    for (size_t i = 1; i < result.size(); ++i)
        if (not isdigit(result[i])) {
            cout <<  "参数不是数字: " << str << endl;
            exit(EXIT_FAILURE);
        }

    return result;
}

// 比较两个数字字符串的大小
int digit_string_compare(const string &lhs, const string &rhs) {
    string lhs_string = digit_string_check_and_format(lhs);
    string rhs_string = digit_string_check_and_format(rhs);

    if (lhs_string[0] == '-' && rhs_string[0] == '-')
        return digit_string_compare(rhs_string.substr(1), lhs_string.substr(1));

    if (lhs_string[0] == '-') return -1;
    if (rhs_string[0] == '-') return +1;

    if (lhs_string.size() < rhs_string.size()) return -1;
    if (lhs_string.size() > rhs_string.size()) return +1;

    if (lhs_string < rhs_string) return -1;
    if (lhs_string > rhs_string) return +1;

    return 0;
}

string sub_digit_string(const string &lhs, const string &rhs);

// 两个数字字符串相加
string add_digit_string(const string &lhs, const string &rhs) {
    string lhs_string = digit_string_check_and_format(lhs);
    string rhs_string = digit_string_check_and_format(rhs);

    if (lhs_string == "0") return rhs_string;
    if (rhs_string == "0") return lhs_string;

    if (lhs_string[0] == '-')
        return sub_digit_string(rhs_string, lhs_string.substr(1));
    if (rhs_string[0] == '-')
        return sub_digit_string(lhs_string, rhs_string.substr(1));

    auto lhs_string_it = lhs_string.crbegin();
    auto rhs_string_it = rhs_string.crbegin();

    int last = 0;
    string result;

    while (lhs_string_it != lhs_string.crend() ||
            rhs_string_it != rhs_string.crend()) {
        if (lhs_string_it != lhs_string.crend()) last += *lhs_string_it++ - '0';
        if (rhs_string_it != rhs_string.crend()) last += *rhs_string_it++ - '0';
        result.push_back('0' + last % 10);
        last /= 10;
    }
    if (last == 1) result.push_back('1');
    reverse(std::begin(result), std::end(result));
    return result;
}

/*
 * 两个数字字符串相减
 * 必须处理可能存在的前置 0，例如 111 - 110 应该等于 1，而不是 001
 */
std::string sub_digit_string(const std::string &lhs, const std::string &rhs) {
    std::string lhs_string = digit_string_check_and_format(lhs);
    std::string rhs_string = digit_string_check_and_format(rhs);

    if (lhs_string == rhs_string) return "0";

    if (rhs_string == "0") return lhs_string;

    if (lhs_string == "0") {
        if (rhs_string[0] == '-')
            return rhs_string.substr(1);
        else
            return "-" + rhs_string;
    }

    if (lhs_string[0] == '-') {
        std::string result = add_digit_string(lhs_string.substr(1), rhs_string);
        if (result[0] == '-')
            return result.substr(1);
        else
            return '-' + result;
    }

    if (rhs_string[0] == '-')
        return add_digit_string(lhs_string, rhs_string.substr(1));

    if (digit_string_compare(lhs_string, rhs_string) == -1)
        return "-" + sub_digit_string(rhs_string, lhs_string);

    std::string result;

    auto lhs_string_it = lhs_string.crbegin();
    auto rhs_string_it = rhs_string.crbegin();

    int prev = 0;

    while (lhs_string_it != lhs_string.crend() ||
            rhs_string_it != rhs_string.crend()) {
        if (lhs_string_it != lhs_string.crend()) prev += *lhs_string_it++ - '0';
        if (rhs_string_it != rhs_string.crend()) prev -= *rhs_string_it++ - '0';
        if (prev < 0) {
            result.push_back(prev + 10 + '0');
            prev = -1;
        } else {
            result.push_back(prev + '0');
            prev = 0;
        }
    }
    std::reverse(std::begin(result), std::end(result));
    auto index = result.find_first_not_of('0');  // 去除可能存在的前置 0
    return result.substr(index);
}

/*
 * 两个数字字符串相乘
 */
std::string mul_digit_string(const std::string &lhs, const std::string &rhs) {
    std::string lhs_string = digit_string_check_and_format(lhs);
    std::string rhs_string = digit_string_check_and_format(rhs);

    if (lhs_string == "0" || rhs_string == "0") return "0";

    if (lhs_string[0] == '-' && rhs_string[0] == '-')
        return mul_digit_string(lhs_string.substr(1), rhs_string.substr(1));

    if (lhs_string[0] == '-')
        return "-" + mul_digit_string(lhs_string.substr(1), rhs_string);

    if (rhs_string[0] == '-')
        return "-" + mul_digit_string(lhs_string, rhs_string.substr(1));

    // 对于 m 位无符号的数 乘以 n 位无符号的数，
    // 结果至少有 m + n - 1 位，最多有 m + n 位
    std::string result(lhs_string.size() + rhs_string.size(), '0');

    size_t begin_index = 0;
    size_t i = lhs_string.size();
    while (i > 0) {
        --i;
        int last = 0;
        int k = begin_index++;
        int j = rhs_string.size();
        while (j > 0) {
            --j;
            last += (lhs_string[i] - '0') * (rhs_string[j] - '0') + result[k] - '0';
            result[k++] = '0' + last % 10;
            last /= 10;
        }
        if (last != 0) result[k] = result[k] - '0' + last + '0';
    }
    std::reverse(std::begin(result), std::end(result));
    if (result[0] == '0')  // 去掉多余的 0
        return result.substr(1);
    else
        return result;
}

/*
 * 两个数字字符串相除，本函数结果只包含整数部分
 * 如果除数为 0，将退出
 */
std::string div_digit_string(const std::string &lhs, const std::string &rhs) {
    std::string lhs_string = digit_string_check_and_format(lhs);
    std::string rhs_string = digit_string_check_and_format(rhs);

    if (rhs_string == "0") {
        printf("除数不能为 0\n");
        exit(EXIT_FAILURE);
    }

    if (lhs_string == "0") return "0";

    if (lhs_string == rhs_string) return "1";

    if (lhs_string[0] == '-' && rhs_string[0] == '-')
        return div_digit_string(lhs_string.substr(1), rhs_string.substr(1));

    if (lhs_string[0] == '-') {
        std::string result = div_digit_string(lhs_string.substr(1), rhs_string);
        return result == "0" ? "0" : ("-" + result);
    }

    if (rhs_string[0] == '-') {
        std::string result = div_digit_string(lhs_string, rhs_string.substr(1));
        return result == "0" ? "0" : ("-" + result);
    }

    if (digit_string_compare(lhs_string, rhs_string) == -1) return "0";

    std::string result;

    std::string current_str = lhs_string.substr(0, rhs_string.size());
    std::string last_str = lhs_string.substr(rhs_string.size());

    if (digit_string_compare(current_str, rhs_string) == -1) {
        current_str += last_str[0];
        last_str = last_str.substr(1);
    }

    for (;;) {
        int count = 0;
        for (;;) {
            std::string temp = sub_digit_string(current_str, rhs_string);
            if (temp == "0") {
                ++count;
                current_str = "";
                break;
            }
            if (temp[0] == '-') break;
            ++count;
            current_str = temp;
        }
        result.push_back('0' + count);

        if (last_str.empty()) break;

        current_str += last_str[0];
        last_str = last_str.substr(1);
    }

    return result;
}

struct StringDigit {
    string integral; // 整数部分
    string decimal;  // 小数部分

} ;

int main() {
    StringDigit string_digit;

    string_digit.integral = "123";

    cout << string_digit.integral << endl;

    return 0;
}













union Node1 {
    double        val_double;
    unsigned long val_ulong;
};

map<int, string> dict; // 存储 2 的幂次

// 获取浮点数的二进制形式
string double_to_bit(const string& str) {
    stringstream input(str);
    Node1 node;
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

int main1() {

    unsigned char ch = 'a';

    cout << ch << endl;

    return 0;





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

