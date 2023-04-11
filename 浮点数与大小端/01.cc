
#include <bitset>
#include <iostream>
#include <string>

template <typename T>
void test(const std::string& str, T v) {
    char* p = (char*)&v;

    std::cout << str << " ";
    for (int i = 0; i < sizeof(T); ++i) {
        if (i != 0 && i % 8 == 0) {
            std::cout << std::endl << "                   ";
        }
        std::cout << std::bitset<8>(p[i]) << " ";
    }
    std::cout << std::endl;
}

int main() {
    test("       char(1) => ", (char)1);
    test("      short(1) => ", (short)1);
    test("        int(1) => ", (int)1);
    test("       long(1) => ", (long)1);
    test("long   long(1) => ", (long long)1);
    test("      float(1) => ", (float)1);
    test("     double(1) => ", (double)1);
    test("long double(1) => ", (long double)1);
    return 0;
}
