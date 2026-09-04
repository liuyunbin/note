
// scanf 除了 %c 外, 将忽略所有的空白字符
//
//"%c"     # 字符
//         # 输入: 可以读入空白字符
//" %c"    # 输入: 忽略所有的空白字符
//         #       然后读入字符
//         # 输出: 输出空格, 再输出字符
//"%s"     # 字符串
//"%5s"    # 输入: 指定最大宽度
//         #       貌似只对字符串有效
//         # 输出: 指定最小宽度
//         #       默认右对齐
//         #       填充空格
//"%d"     # 十进制整数
//"%-5d"   # 输出: 左对齐
//"%+5d"   # 输出: 有符号的数字,
//         #       如果是正数, 添加前缀 +
//"%05d"   # 输出: 前缀填充 0
//"%u"     # 无符号的  十进制整数
//"%o"     # 无符号的  八进制整数
//"%x"     # 无符号的十六进制整数
//"%i"     #                 整数
//"%f"     # 非科学计数法的浮点数
//"%10.5f" # 指明宽度 和 小数点位数
//         #   四舍六入五取偶
//"%e"     #   科学计数法的浮点数
//"%g"     #               浮点数
//"%p"     #               指针
//"%*d"    # 输入: 忽略这个数据
//         # 输出: 指定宽度
//
// getchar()         # 读取一个字符,   包含空白字符
// cin >> ch         # 读取一个字符, 不包含空白字符
// cin.get(ch)       # 读取一个字符,   包含空白字符
//
// fgets()           # 读取一行,   包含换行符
// getline(cin, str) # 读取一行, 不包括换行符
//

#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string str = "123";

#if 0
    // 设置输入的最大宽度
    // 只对字符串有效
    // 只对下一位有效-不准确
    cin  >> setw(5) >> str;
    cout << str << "end" << endl;

    // skipws-输入跳过前导空白符
    // noskipws-输入不跳过前导空白符

#endif

    str = "123";
    cout << "            字符串: " << str << endl;
    // setw 只对下一位有效-不准确
    cout << " 输出的最小宽度(5): " << setw(5) << str << endl;
    cout << "     填充字符为(*): " << setfill('*') << setw(5) << str << endl;
    cout << "            左对齐: " << left << setw(5) << str << endl;
    cout << "            右对齐: " << right << setw(5) << str << endl;
    cout << "恢复填充字符为空格" << endl << setfill(' ');
    int n = 18;
    cout << "              整数: " << n << endl;
    cout << "          十六进制: " << hex << n << endl;
    cout << "            八进制: " << oct << n << endl;
    cout << "            十进制: " << dec << n << endl;
    cout << "      显示进制前缀: " << showbase << hex << n << endl;
    cout << "前缀  使用大写字母: " << uppercase << hex << n << endl;
    cout << "前缀不使用大写字母: " << nouppercase << hex << n << endl;
    cout << "    不显示进制前缀: " << noshowbase << hex << n << endl;
    double x = 1.0;
    cout << "              小数: " << x << endl;
    cout << "正数包含  前置加号: " << showpos << x << endl;
    cout << "正数包含不前置加号: " << noshowpos << x << endl;
    cout << "    始终包含小数点: " << showpoint << x << endl;
    cout << "  不始终包含小数点: " << noshowpoint << x << endl;
    cout << "  以科学表示法输出: " << scientific << x << endl;
    cout << "不以科学表示法输出: " << fixed << x << endl;
    cout << "    保留 10 位小数: " << setprecision(10) << x << endl;
    cout << "      默认舍入模式: 四舍六入五取偶" << endl;
    cout << "   bool 类型 false: " << boolalpha << false << endl;
    cout << "   bool 类型  true: " << boolalpha << true << endl;
    cout << "   数值 类型 false: " << noboolalpha << false << endl;
    cout << "   数值 类型  true: " << noboolalpha << true << endl;

    // 全缓存
    // * 程序结束
    // * 缓冲区满
    // * 手动刷新缓存
    // * 涉及磁盘文件一般是全缓存
    // 行缓冲
    // * 程序结束
    // * 缓冲区满
    // * 遇到文件结束符
    // * 手动刷新缓存
    // * 涉及终端一般是行缓存
    // 无缓冲
    // * 涉及终端输出错误是无缓存
    cout << endl << "测试  自动刷新缓冲" << endl;
    cout << unitbuf;  // 每次调用都自动刷新缓冲区
    cout << "暂停5s...";
    sleep(5);
    cout << "完成" << endl;

    cout << endl << "测试不自动刷新缓冲" << endl;
    cout << nounitbuf;  // 不自动刷新缓冲区
    cout << "暂停5s...";
    sleep(5);
    cout << "完成" << endl;

    return 0;
}
