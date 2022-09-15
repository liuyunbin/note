#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <bitset>
#include <iomanip>
#include <algorithm>

using namespace std;

string arr[52];

// 字符串浮点数加法
// x y 的小数部分始终为 0
// x y 至少三位
string add(string x, string y) {
    if (x.size() > y.size()) {
        return add(y, x);
    }
    x += string(y.size() - x.size(), '0');

    int sum = 0;
    string z;

    for (size_t i = x.size() - 1; i > 1; --i) {
        sum += (x[i] - '0') + (y[i] - '0');
        z  = string(1, '0' + sum%10) + z;
        sum /= 10;
    }
    return string(1, '0' + sum) + "." + z;
}

string div(string x) {
    string z = "0.";
    int sum = 0;

    for (size_t  i = 2; i < x.size(); ++i){
        sum = sum * 10 + (x[i] - '0');
        z += string(1, sum / 2 + '0');
        sum %= 2;
    }
    if (sum != 0) {
        z += "5";
    }
    return z;
}

void output(const string& str) {
    string s_str = str.substr(0, 1);
    string e_str = str.substr(1, 11);
    string f_str = str.substr(12);

    unsigned long e_int = (unsigned long)bitset<32>(e_str).to_ulong();

    double x = *(double*)str.data();

    string result="0.0";
    for (size_t i = 0; i < f_str.size(); ++i)
        if (f_str[i] == '1')
            result = add(result, arr[i]);

    cout << setiosflags(ios::fixed) <<setprecision(60); // 使用点分输出
                                                        // 设置精度
    cout << "            符号位: " << s_str << endl;
    cout << "              阶码: " << e_str << " --> " << e_int << " --> " << e_int - 1023 << endl;
    cout << "              尾码: " << f_str << endl;
    cout << "        十进制尾码: " << result << endl;
    cout << "              小数: " << x << std::endl;
}

int main() {
    string str= "0.5";
    for (int i = 0; i < 52; ++i) {
        arr[i] = str;
        str = div(str);
    }

    for (;;) {
        cout << endl;
        cout << "本程序将:"                << endl;
        cout << "  自动忽略行内空格"       << endl;
        cout << "  不足 64 位将用 0 补齐"  << endl;
        cout << "  超过 64 位的部分将忽略" << endl;
        cout << "请输入浮点数的二进制: ";

        string str;
        getline(cin, str);

        string str_format(64, '0');
        bool input_ok = true;
        for (size_t  i = 0, k = 0; i < str.size() && k < 64; ++i) {
            if (str[i] == ' ' || str[i] == '\t') {
                continue;
            }
            if (str[i] != '0' && str[i] != '1') {
                cout << str[i] << " 非法" << endl;
                input_ok = false;
                break;
            }
            str_format[k++] = str[i];
        }
        if (input_ok)
            output(str_format);
    }
    return 0;
}

