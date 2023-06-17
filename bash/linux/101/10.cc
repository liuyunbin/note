
#ifndef LOG_H_
#define LOG_H_

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

#endif

void test(char* p) {
    for (int i = 0; p[i] != '\0'; ++i) {
        std::cout << std::hex << (unsigned int)p[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    char utf8_1[] = "中";
    char utf8_2[] = "\u4e2d";
    char16_t utf16[] = u"中";
    char32_t utf32[] = U"中";

    std::cout << "utf-8      中: " << utf8_1 << std::endl;
    std::cout << "utf-8  \\u4e2d: " << utf8_2 << std::endl;
    std::cout << "utf8   sizeof: " << sizeof(utf8_1) << std::endl;
    std::cout << "utf16  sizeof: " << sizeof(utf16) << std::endl;
    std::cout << "utf32  sizeof: " << sizeof(utf32) << std::endl;

    test(utf8_1);
    test((char*)utf16);
    test((char*)utf32);

    return 0;
}
