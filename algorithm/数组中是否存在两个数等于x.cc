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
    cout << "����Ԫ�ظ����� ";
    cin >> n;
    int* a = new int[n];
    cout << "�����������Ԫ�أ� ";
    for (int i = 0; i != n; ++i) cin >> a[i];
    quick_sort(a, 0, n - 1);
    int x;
    cout << "����x: ";
    cin >> x;
    if (find(a, n, x))
        cout << "����" << endl;
    else
        cout << "������" << endl;

    return 0;
}