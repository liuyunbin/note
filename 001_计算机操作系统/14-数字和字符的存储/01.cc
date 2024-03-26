
#include "log.h"

template <typename T>
union Node {
    char str[sizeof(T)];
    T    t;
};

template <typename T>
void test(const std::string& str, T v) {
    Node<T> node;
    node.t = v;

    std::string msg = str + " ";
    for (size_t i = 0; i < sizeof(T); ++i) {
        if (i != 0 && i % 4 == 0) {
            msg += "\n" + std::string(58, ' ');
        }
        msg += std::bitset<8>(node.str[i]).to_string() + " ";
    }
    log(msg);
}

int main() {
    log();
    log("测试字节序");
    log();

    test("测试        char 存储数字 1 => ", (char)1);
    test("测试       short 存储数字 1 => ", (short)1);
    test("测试         int 存储数字 1 => ", (int)1);
    test("测试        long 存储数字 1 => ", (long)1);
    test("测试 long   long 存储数字 1 => ", (long long)1);
    test("测试       float 存储数字 1 => ", (float)1);
    test("测试      double 存储数字 1 => ", (double)1);
    test("测试 long double 存储数字 1 => ", (long double)1);
    test("测试     wchar_t 存储数字 1 => ", (wchar_t)1);
    //    test("测试     char8_t 存储数字 1 => ", (char8_t)1); C++20
    test("测试    char16_t 存储数字 1 => ", (char16_t)1);
    test("测试    char32_t 存储数字 1 => ", (char32_t)1);

    Node<short> node;
    node.t = 1;

    std::string msg = "测试本机的大小端 => ";
    msg += node.str[0] == 1 ? "小端存储" : "大端存储";
    log(msg);

    log();
    log("主进程正常退出");
    log();
    return 0;
}
