
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <setjmp.h>

void log(const std::string& msg) {
    std::cout << "进程(" << getpid() <<  "): " << msg << std::endl;
}

int main() {
    log("测试空指针异常");
    int* p = NULL;
    *p = 10;

    return 0;
}

