
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <bitset>
#include <cctype>
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

#include "20100.h"

std::string get_time() {
    time_t now = time(NULL);
    struct tm* info = localtime(&now);
    char buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    return buf;
}

void log(const std::string& msg = "") {
    std::cout << get_time() << " " << msg << std::endl;
}

void test(const std::string& name, const std::string& bit) {
    Double d(bit);

    std::cout << "        测试类型: " << name << std::endl;
    std::cout << "    测试的二进制: " << d.bit_by_test << std::endl;
    std::cout << "    存储的二进制: " << d.bit_by_cs << std::endl;
    std::cout << "          手动值: " << d.double_by_hand << std::endl;
    std::cout << "          存储值: " << d.double_by_cs << std::endl;
    std::cout << std::endl;
}

void test() {
    std::cout << "测试存储时的四舍六入五取偶" << std::endl << std::endl;

    std::cout << "        舍入方向: " << dict_round[fegetround()] << std::endl;

    test("测试 最后一位是 0, 多余位是 00(舍)",
         "0100001100110000000000000000000000000000000000000000000000000000 00");

    test("测试 最后一位是 0, 多余位是 01(舍)",
         "0100001100110000000000000000000000000000000000000000000000000000 01");

    test("测试 最后一位是 0, 多余位是 10(舍, 取偶)",
         "0100001100110000000000000000000000000000000000000000000000000000 10");

    test("测试 最后一位是 0, 多余位是 11(入)",
         "0100001100110000000000000000000000000000000000000000000000000000 11");

    test("测试 最后一位是 1, 多余位是 00(舍)",
         "0100001100110000000000000000000000000000000000000000000000000001 00");

    test("测试 最后一位是 1, 多余位是 01(舍)",
         "0100001100110000000000000000000000000000000000000000000000000001 01");

    test("测试 最后一位是 1, 多余位是 10(入, 取偶)",
         "0100001100110000000000000000000000000000000000000000000000000001 10");

    test("测试 最后一位是 1, 多余位是 11(入)",
         "0100001100110000000000000000000000000000000000000000000000000001 11");
}

int main() {
    init();
    test();
    return 0;
}
