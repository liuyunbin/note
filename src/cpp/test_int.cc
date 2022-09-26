
// 原码: 正数: 最高位添加 0, 负数: 最高位添加 1
// 反码: 正数: 等于原码, 负数: 在原码的基础上, 除符号位外, 各位取反
// 补码: 正数: 等于原码
//       负数: 在反码的基础上, 加 1
//       优点: 方便计算,
// 移码: 加上指定数字, 使其全部变正
//
// 整数区分大小端
//

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

// 移除所有的 空字符
string trim(const string& str) {
    string result;
    for (char ch : str)
        if (!isspace(ch)) result += ch;
    return result;
}

// 计算机计算的结果
union Node {
    int x;
    unsigned int y;
    char s[4];

    string to_bit() {
        string result;

        for (int i = 0; i < 32; i += 8)
            result += bitset<32>(y).to_string().substr(i, 8) + " ";

        return result;
    }

    //string to_bit() { return bit_to_string(bitset<64>(y).to_string()); }

    //// 计算机 实际存储
    //string get_mem() {
    //    string result;
    //    for (int i = 0; i < 8; ++i)
    //        result += bitset<8>((unsigned char)s[i]).to_string() + " ";
    //    return result;
    //}
};

void test(int v) {
    Node node;
    node.x = v;
    cout << v << " -> " << node.to_bit() << endl;
}

int main() {
    //Node node;
    //int x = 22;
    //string bit = "1001"
    cout << "十进制数字  (22)   --> 二进制字符串(" << bitset<32>(22).to_string() << ")" << endl;
    cout << "二进制字符串(1001) --> 十进制数字  (" << bitset<32>("1001").to_ulong() << ")" << endl;


    cout << endl;
    test(2);
    test(1);
    test(0);
    test(-1);
    test(-2);






    return 0;
}
