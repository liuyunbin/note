#include <iostream>

using namespace std;

int main() {
    int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n;
    cin >> n;
    int* a = new int[n + 1];
    int* b = new int[n + 1];
    for (int i = 0; i != n; ++i) {
        a[i] = 0;
        b[i] = 0;
    }
    for (int i = 1; i != n + 1; ++i)
        for (int j = 1; j != i + 1; ++j)
            if (a[i] < a[i - j] + p[j]) {
                a[i] = p[j] + a[i - j];
                b[i] = j;
            }

    cout << a[n] << endl;
    for (int i = n; i != 0; i -= b[i]) cout << b[i] << " ";
    cout << endl;

    return 0;
}