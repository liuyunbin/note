
#include "log.h"

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
