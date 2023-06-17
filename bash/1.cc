#include <sys/time.h>
#include <time.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::string test1(double sum, std::vector<double>& res_double,
                  std::vector<std::string>& res_string,
                  std::vector<int>& res_int) {
    int index = res_double.size() - 1;
    char buf[64];
    snprintf(buf, sizeof(buf), "%.2f", res_double[index] / sum * 100);
    return buf;
}

std::string test2(double sum, std::vector<double>& res_double,
                  std::vector<std::string>& res_string,
                  std::vector<int>& res_int) {
    sum = 0;
    unsigned long long n = res_double.size() - 1;
    for (unsigned long long i = 0; i < n; ++i) {
        sum += res_double[i];
    }
    char buf[64];
    snprintf(buf, sizeof(buf), "%.2f", 100 - sum);
    return buf;
}

std::string test3(double sum, std::vector<double>& res_double,
                  std::vector<std::string>& res_string,
                  std::vector<int>& res_int) {
    int sum_int = 10000;
    for (int v : res_int) {
        sum_int -= v;
    }
    std::string str = std::to_string(sum_int);
    if (str.size() < 3) {
        str.insert(0, 3 - str.size(), '0');
    }
    str.insert(str.end() - 2, '.');
    return str;
}

using type = std::string (*)(double sum, std::vector<double>& res_double,
                             std::vector<std::string>& res_string,
                             std::vector<int>& res_int);

void test(const std::string& name, type f, double sum,
          std::vector<double>& res_double, std::vector<std::string>& res_string,
          std::vector<int>& res_int) {
    struct timeval t1;
    struct timeval t2;
    gettimeofday(&t1, NULL);
    std::string res = f(sum, res_double, res_string, res_int);
    gettimeofday(&t2, NULL);
    std::cout << name << res << " => " << t2.tv_sec - t1.tv_sec << " "
              << t2.tv_usec - t1.tv_usec << std::endl;
}

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 100000);
    unsigned long long n = 10000;

    if (argc > 1) {
        n = atoll(argv[1]);
    }

    std::vector<double> res_double;
    std::vector<std::string> res_string;
    std::vector<int> res_int;

    double sum = 0;
    for (unsigned long long i = 0; i < n; ++i) {
        double v = dis(gen);
        sum += v;
        res_double.push_back(v);
    }

    std::sort(res_double.begin(), res_double.end());
    for (unsigned long long i = 0; i < n - 1; ++i) {
        double v = res_double[i];
        char buf[64];
        snprintf(buf, sizeof(buf), "%.2f", v / sum * 100);
        res_string.push_back(buf);
        res_double[i] = atof(buf);
        std::string str = buf;
        str.erase(str.end() - 3);
        res_int.push_back(atoll(str.data()));
    }

    std::cout << "  测试数量: " << n << std::endl;
    std::cout << "最后一个值: " << res_double.back() << std::endl;
    std::cout << "      总和: " << std::fixed << sum << std::endl;
    test("    直接算: ", test1, sum, res_double, res_string, res_int);
    test("  浮点数算: ", test2, sum, res_double, res_string, res_int);
    test("  字符串算: ", test3, sum, res_double, res_string, res_int);

    return 0;
}
