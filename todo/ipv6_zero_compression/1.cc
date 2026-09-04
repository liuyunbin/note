
#include <iostream>
#include <string>
#include <vector>

void string_to_vector(const std::string&        str,
                      const std::string&        sep,
                      std::vector<std::string>& vec) {
    if (str.empty() || sep.empty())
        return;

    size_t pos = 0;
    for (;;) {
        size_t next_pos = str.find_first_of(sep, pos);
        if (next_pos == std::string::npos) {
            vec.push_back(str.substr(pos));
            break;
        } else {
            vec.push_back(str.substr(pos, next_pos - pos));
            pos = next_pos + 1;
        }
    }
}

bool zero_compression(const std::string& in, std::string& out) {
    if (in.find(':') == std::string::npos)
        return false;  // ipv4

    // 1. 切割 ipv6
    std::vector<std::string> vec;
    string_to_vector(in, ":", vec);

    // 2. 去掉每一段前置的 0
    for (auto& d : vec) {
        size_t first_not_zero = d.find_first_not_of('0');
        if (first_not_zero == std::string::npos)
            d = "0";  // 全是0的话返回 0
        else
            d = d.substr(first_not_zero);
    }

    // 3. 查找最长的连续的 0
    int index = -1, len = 0;
    for (int i = 0; i < vec.size();) {
        int j = i;
        while (j < vec.size() && vec[j] == "0")
            ++j;
        if (j - i > len && j - i > 1) {  // 单字段0不压缩
            len   = j - i;
            index = i;
        }
        i = j + 1;
    }

    // 4. 压缩合并
    for (int i = 0; i < vec.size();) {
        if (i == index)
            i = index + len;
        else
            out += vec[i++];
        out += ":";
    }

    // 5. 去除最后的多余的:
    if (!out.empty())
        out.pop_back();

    // 6. 处理全是 0 的特殊情况
    if (out.empty())
        out = "::";
    return true;
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
