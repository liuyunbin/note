#include <iomanip>
#include <iostream>

using namespace std;

void trial(int* a, const int& k, const int& n) {
    if (k == n) {
        for (int i = 0; i != n; ++i) cout << setw(3) << a[i];
        cout << endl;
    } else {
        for (int i = 0; i != n; ++i) {
            int j = 0;
            a[k] = i;
            while (j != k) {
                if (a[k] == a[j] || k - j == a[k] - a[j] ||
                    k - j == a[j] - a[k])
                    break;
                ++j;
            }
            if (j == k) trial(a, k + 1, n);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    trial(a, 0, n);

    return 0;
}