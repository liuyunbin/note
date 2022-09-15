//
// double 区分大小端
// 1-符号位 11-阶码(偏移量 1023) 52-尾码
// +0,-0    00000000000          全为0   非规约, 没有前置 1
// +1,-1    01111111111          全为0     规约,   有前置 1
// 无穷     11111111111          全为0     规约,   有前置 1 ??
// 异常数字 11111111111        非全为0
// 非规约数 00000000000        非全为0   非规约, 没有前置 0
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

void output(double x) {
    unsigned char* p = (unsigned char*)(&x);
    unsigned long y = *(unsigned long*)p;

    string str = bitset<64>(y).to_string();
    string s = str.substr(0, 1);
    string e_str = str.substr(1, 11);
    int    e_int = (int)bitset<32>(e_str).to_ulong();
    string f_str = str.substr(12);

    string result="0.0";
    for (size_t i = 0; i < f_str.size(); ++i)
        if (f_str[i] == '1')
            result = add(result, arr[i]);

    cout << setiosflags(ios::fixed) <<setprecision(60);
    cout << "            符号位: " << s << endl;
    cout << "              阶码: " << e_str << endl;
    cout << "        十进制阶码: " << e_int << endl;
    cout << "去偏移的十进制阶码: " << e_int - 1023 << endl;
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

    output(+0);
    output(-0);

    double x;
    for (;;) {
        cout << endl << "请输入浮点数: ";
        if (cin  >> x) {
            output(x);
            //cout << div(to_string(x)) << endl;
        } else {
            break;
        }
    }
    return 0;
}

