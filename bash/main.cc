#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> zcss = {
        "32.12", "50.39", "55.33", "91.91", "94.30", "51.38", "53.33",
        "57.93", "66.65", "95.27", "44.35", "41.15", "95.37", "88.44",
        "58.13", "94.49", "94.87", "56.00", "86.96", "56.31"};

    std::vector<double> res;
    double sum = 0;
    for (std::string& s : zcss) {
        double v = std::atof(s.data());
        sum += v;
        res.push_back(v);
    }

    int sum_zb = 0;
    for (double v : res) {
        char buf[64];
        snprintf(buf, sizeof(buf), "%.2f", v / sum * 100);
        std::string str = buf;
        std::cout << str << std::endl;
        str.erase(str.end() - 3);
        sum_zb += std::atoi(str.data());
    }

    std::cout << "sum = " << sum_zb << std::endl;

    return 0;
}
