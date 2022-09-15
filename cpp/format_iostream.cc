
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <bitset>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    cout << "        除了 setw 只对下一位有效外, 其他都会保留这个状态: " << endl << endl;

    cout << "                                        设置输出宽度(10): " << setw(10) << 17 << endl;

    cout << setfill('*');
    cout << "                                        设置填充字符( *): " << setw(10) << 17 << endl;

    cout << "                                  设置左对齐, 默认右对齐: " << left << setw(10) << 17 << endl;
    cout << "                                  设置右对齐, 默认右对齐: " << right << setw(10) << 17 << endl;

    cout << setfill(' ');
    cout << "                        设置整数十六进制输出, 默认十进制: " << hex << 17 << endl;
    cout << "                        设置整数  八进制输出, 默认十进制: " << oct << 17 << endl;
    cout << "                        设置整数  十进制输出, 默认十进制: " << dec << 17 << endl;

    double x = 12.345047;
    x = 0.00345;
    double y = 0.000000000000000123333333333333333333333456789;
    double z = 1233333333333333333333334567.89;

    cout << "                            浮点数默认输出, 默认六位精度: " << endl;
    cout << "                                              浮点数正常: " << x << endl;
    cout << "                                              浮点数过小: " << y << endl;
    cout << "                                              浮点数过大: " << z << endl;

    cout << "                                  设置不省略小数点后的 0: " << showpoint << x << endl;
    cout << "                                   设置浮点数整体精度(3): " << setprecision(3) << x << endl;

    cout << "设置浮点数始终  以科学表示法输出, 精度变为小数点后的位数: " << endl;
    cout << scientific;
    cout << "                                              浮点数正常: " << x << endl;
    cout << "                                              浮点数过小: " << y << endl;
    cout << "                                              浮点数过大: " << z << endl;

    cout << "设置浮点数始终不以科学表示法输出, 精度变为小数点后的位数: " << endl;
    cout << fixed;
    cout << "                                              浮点数正常: " << x << endl;
    cout << "                                              浮点数过小: " << y << endl;
    cout << "                                              浮点数过大: " << z << endl;

    cout << boolalpha;
    cout << "                              输出字符串形式的 bool 类型: " << false << endl;

    return 0;
}
