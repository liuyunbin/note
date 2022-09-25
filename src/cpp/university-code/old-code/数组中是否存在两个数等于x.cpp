#include <iomanip>
#include <iostream>

using namespace std;

int partition(int* a, const int& low, const int& high) {
    int key = a[low];
    int i = low;
    int j = high;
    while (i != j) {
        while (i != j && a[j] >= key) --j;
        a[i] = a[j];
        while (i != j && a[i] <= key) ++i;
        a[j] = a[i];
    }
    a[i] = key;
    return i;
}

void quick_sort(int* a, const int& low, const int& high) {
    if (low < high) {
        int mid = partition(a, low, high);
        quick_sort(a, low, mid - 1);
        quick_sort(a, mid + 1, high);
    }
}

bool find(int*& a, const int& n, const int& x) {
    int i = 0;
    int j = n - 1;
    while (i != j) {
        if (a[i] + a[j] == x) {
            return true;
        } else {
            if (a[i] + a[j] > x)
                --j;
            else
                ++i;
        }
    }
    return false;
}

int main() {
    int n;
    cout << "输入元素个数： ";
    cin >> n;
    int* a = new int[n];
    cout << "依次输入各个元素： ";
    for (int i = 0; i != n; ++i) cin >> a[i];
    quick_sort(a, 0, n - 1);
    int x;
    cout << "输入x: ";
    cin >> x;
    if (find(a, n, x))
        cout << "存在" << endl;
    else
        cout << "不存在" << endl;

    return 0;
}