
#include "test.h"

int main() {
    init();

    double x = numeric_limits<double>::denorm_min();
    string str = to_double_cs(x);

    cout << "最小非规约正数: " << str << endl;
    cout << "小数点后共有: " << str.size() - 2 << " 位" << endl;
    cout << endl;

    return 0;
}
