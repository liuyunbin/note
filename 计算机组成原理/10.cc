
#include <iostream>
#include <string>

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
