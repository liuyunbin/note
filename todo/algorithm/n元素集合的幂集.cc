#include <iomanip>
#include <iostream>

using namespace std;

void powerset(int (*a)[2], const int& k, const int& n) {
    if (k != n) {
        a[k][1] = 1;
        powerset(a, k + 1, n);
        a[k][1] = 0;
        powerset(a, k + 1, n);
    } else {
        for (int i = 0; i != n; ++i)
            if (a[i][1] == 1) cout << setw(3) << a[i][0];
        cout << endl;
    }
}

int main() {
    cout << "请输入元素的个数： ";
    int n;
    cin >> n;
    int(*a)[2] = new int[n][2];
    cout << "依次输入各个元素： ";
    for (int i = 0; i != n; ++i) cin >> a[i][0];
    powerset(a, 0, n);

    return 0;
}