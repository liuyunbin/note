
#include <arpa/inet.h>

#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> zero_compression(const std::string& in) {
    struct in6_addr addr;
    char            buf[INET6_ADDRSTRLEN];
    if (inet_pton(AF_INET6, in.c_str(), &addr) == 1 &&
        inet_ntop(AF_INET6, &addr, buf, sizeof(buf)) != NULL)
        return std::string(buf);
    return std::nullopt;
}

void test(const std::string& in, const std::string& out) {
    auto res = zero_compression(in);
    if (res && *res == out)
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
