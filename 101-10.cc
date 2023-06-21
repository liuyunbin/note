
#include "log.h"

void test(const std::string& name, char* p, size_t n) {
    log(name);
    std::string msg;
    for (size_t i = 0; i < n; ++i) {
        log("第", i + 1, "个字节: ", format("%x", p[i]));
    }
}

int main() {
    log();
    log("测试 UTF-8");
    log();

    char     utf8_1[] = "中";
    char     utf8_2[] = "\u4e2d";
    char16_t utf16[]  = u"中";
    char32_t utf32[]  = U"中";

    log("utf-8      中: ", utf8_1);
    log("utf-8  \\u4e2d: ", utf8_2);
    log("utf8   sizeof: ", sizeof(utf8_1));
    log("utf16  sizeof: ", sizeof(utf16));
    log("utf32  sizeof: ", sizeof(utf32));

    test("UTF-8  在内存中的存储: ", utf8_1, sizeof(utf8_1));
    test("UTF-16 在内存中的存储: ", (char*)utf16, sizeof(utf16));
    test("UTF-32 在内存中的存储: ", (char*)utf32, sizeof(utf32));

    log();
    log("主进程正常退出");
    log();
    return 0;
}
