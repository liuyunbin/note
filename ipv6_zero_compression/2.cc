
#include <arpa/inet.h>

#include <iostream>
#include <string>

bool zero_compression(const std::string& in, std::string& out) {
    struct in6_addr addr;
    char            buf[INET6_ADDRSTRLEN];
    if (inet_pton(AF_INET6, in.c_str(), &addr) == 1 &&
        inet_ntop(AF_INET6, &addr, buf, sizeof(buf)) != NULL) {
        out = std::string(buf);
        return true;
    }
    return false;
}

void test(const std::string& in, const std::string& out) {
    std::string res;
    if (zero_compression(in, res) && res == out)
        std::cout << "success: " << in << std::endl;
    else
        std::cout << "  error: " << in << std::endl;
}

int main() {
    test("1234:1234:1234:1234:1234:1234:1234:0000",
         "1234:1234:1234:1234:1234:1234:1234:0");
    test("1234:1234:1234:1234:1234:1234:1234:000a",
         "1234:1234:1234:1234:1234:1234:1234:a");
    test("1234:0:1234:1234:1234:1234:1234:1234",
         "1234:0:1234:1234:1234:1234:1234:1234");
    test("1234:0000:0000:1234:0000:0000:1234:1234", "1234::1234:0:0:1234:1234");
    test("0000:0000:0000:0000:0000:0000:0000:0000", "::");
    test("1234:0000:0000:1234:0000:0000:0000:1234", "1234:0:0:1234::1234");
    test("127.0.0.1", "127.0.0.1");
    return 0;
}
