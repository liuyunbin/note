
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

#include "101-00.h"

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

void test(const std::string& str, double x) {
    std::cout << str << " => " << Double(x).double_by_cs << std::endl;
}

int main() {
    init();

    test("4503599627370496.0", 4503599627370496.0);
    test("4503599627370496.1", 4503599627370496.1);
    test("4503599627370496.2", 4503599627370496.2);
    test("4503599627370496.3", 4503599627370496.3);
    test("4503599627370496.4", 4503599627370496.4);
    test("4503599627370496.5", 4503599627370496.5);
    test("4503599627370496.6", 4503599627370496.6);
    test("4503599627370496.7", 4503599627370496.7);
    test("4503599627370496.8", 4503599627370496.8);
    test("4503599627370496.9", 4503599627370496.9);
    test("4503599627370490", 4503599627370490);
    test("4503599627370491", 4503599627370491);
    test("4503599627370492", 4503599627370492);
    test("4503599627370493", 4503599627370493);
    test("4503599627370494", 4503599627370494);
    test("4503599627370495", 4503599627370495);
    test("4503599627370496", 4503599627370496);
    test("4503599627370497", 4503599627370497);
    test("4503599627370498", 4503599627370498);
    test("4503599627370499", 4503599627370499);

    return 0;
}
