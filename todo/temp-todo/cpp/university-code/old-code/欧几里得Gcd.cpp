#include <iostream>

using namespace std;

int main() {
    int m;
    int n;
    cin >> m >> n;
    if (m < n) {
        int temp = m;
        m = n;
        n = temp;
    }
    while (n != 0) {
        int temp = m % n;
        m = n;
        n = temp;
    }

    cout << "m, n 的最大公约数为：" << m << endl;

    return 0;
}