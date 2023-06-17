
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

int main() {
    init();

    double x = std::numeric_limits<double>::denorm_min();

    Double d(x);

    std::string str = d.double_by_cs;

    std::cout << "最小非规约正数: " << str << std::endl;
    std::cout << "小数点后共有: " << str.size() - 2 << " 位" << std::endl;
    std::cout << std::endl;

    return 0;
}
