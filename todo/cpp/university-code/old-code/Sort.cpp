#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

class Sort {
   private:
    int* a;
    int n;
    int k;

   public:
    Sort() : a(0), n(0), k(0) {}

    void init() {
        n = 10;
        a = new int[n];
        for (int i = 0; i != n; ++i) a[i] = rand() % 100;
        k = 5;
    }

    void swap(int& x, int& y) const {
        int temp = x;
        x = y;
        y = temp;
    }

    void output() {
        for (int i = 0; i != n; ++i) cout << setw(5) << a[i];
        cout << endl;
        delete[] a;
        a = 0;
    }

    //—°‘ÒÀ„∑®
    void choose_sort() {
        init();
        choose_sort(0, n - 1);
        cout << "—°‘ÒÀ„∑®£∫ ";
        output();
    }
    void choose_sort(const int& low, const int& high) {
        for (int i = low; i != high; ++i) {
            int key = i;
            for (int j = i + 1; j != high + 1; ++j) {
                if (a[key] > a[j]) key = j;
            }
            if (key != i) swap(a[key], a[i]);
        }
    }

    //√∞≈›≈≈–Ú
    void bubble_sort() {
        init();
        bubble_sort(0, n - 1);
        cout << "√∞≈›≈≈–Ú£∫ ";
        output();
    }
    void bubble_sort(const int& low, const int& high) {
        for (int i = low; i != high; ++i) {
            for (int j = high; j != i; --j) {
                if (a[j] < a[j - 1]) swap(a[j], a[j - 1]);
            }
        }
    }

    //À´√∞≈›≈≈–Ú
    void double_bubble_sort() {
        init();
        double_bubble_sort(0, n - 1);
        cout << "À´√∞≈›≈≈–Ú£∫ ";
        output();
    }
    void double_bubble_sort(const int& low, const int& high) {
        int i = low;
        int j = high;
        while (i != j) {
            int temp = i;
            for (int k = i; k != j; ++k) {
                if (a[k] > a[k + 1]) {
                    swap(a[k], a[k + 1]);
                    temp = k;
                }
            }
            j = temp;
            for (int k = j; k != i; --k) {
                if (a[k] < a[k - 1]) {
                    swap(a[k], a[k - 1]);
                    temp = k;
                }
            }
            i = temp;
        }
    }

    //÷±Ω”≤Â»Î≈≈–Ú
    void straight_insert_sort() {
        init();
        straight_insert_sort(0, n - 1);
        cout << "÷±Ω”≤Â»Î≈≈–Ú£∫ ";
        output();
    }
    void straight_insert_sort(const int& low, const int& high) {
        for (int i = low + 1; i != high + 1; ++i) {
            int key = a[i];
            int j = i;
            while (j != low && a[j - 1] > key) {
                a[j] = a[j - 1];
                --j;
            }
            a[j] = key;
        }
    }

    //’€∞Î≤Â»Î≈≈–Ú
    void insert_sort() {
        init();
        insert_sort(0, n - 1);
        cout << "’€∞Î≤Â»Î≈≈–Ú£∫ ";
        output();
    }
    void insert_sort(const int& low, const int& high) {
        for (int k = low + 1; k != high + 1; ++k) {
            int key = a[k];
            int i = low;
            int j = k - 1;
            while (i <= j) {
                int mid = (i + j) / 2;
                if (a[mid] > key)
                    j = mid - 1;
                else
                    i = mid + 1;
            }
            for (j = k; j != i; --j) a[j] = a[j - 1];
            a[i] = key;
        }
    }

    //µ›πÈ≤Â»Î≈≈–Ú
    void insert_sort_digui() {
        init();
        insert_sort_digui(0, n - 1);
        cout << "µ›πÈ≤Â»Î≈≈–Ú£∫ ";
        output();
    }
    void insert(const int& low, const int& high) {
        int key = a[high];
        int i = high;
        while (i != low && a[i - 1] > key) {
            a[i] = a[i - 1];
            --i;
        }
        a[i] = key;
    }
    void insert_sort_digui(const int& low, const int& high) {
        if (low != high) {
            insert_sort_digui(low, high - 1);
            insert(low, high);
        }
    }

    //πÈ≤¢≈≈–Ú
    void merge_sort() {
        init();
        merge_sort(0, n - 1);
        cout << "πÈ≤¢≈≈–Ú£∫ ";
        output();
    }
    void merge(const int& low, const int& mid, const int& high) {
        int* p = new int[high - low + 1];
        int i = low;
        int j = mid + 1;
        int k = 0;
        while (i != mid + 1 && j != high + 1) {
            if (a[i] < a[j])
                p[k++] = a[i++];
            else
                p[k++] = a[j++];
        }
        while (i != mid + 1) p[k++] = a[i++];
        while (j != high + 1) p[k++] = a[j++];
        for (i = low; i != high + 1; ++i) a[i] = p[i - low];
        delete[] p;
        p = 0;
    }
    void merge_sort(const int& low, const int& high) {
        if (low < high) {
            int mid = (low + high) / 2;
            merge_sort(low, mid);
            merge_sort(mid + 1, high);
            merge(low, mid, high);
        }
    }

    //πÈ≤¢≤Â»Î≈≈–Ú
    void merge_insert_sort() {
        init();
        merge_insert_sort(0, n - 1);
        cout << "πÈ≤¢≤Â»Î≈≈–Ú£∫ ";
        output();
    }
    void merge_insert_sort(const int& low, const int& high) {
        if (high - low < k)
            straight_insert_sort(low, high);
        else {
            int mid = (low + high) / 2;
            merge_insert_sort(low, mid);
            merge_insert_sort(mid + 1, high);
            merge(low, mid, high);
        }
    }

    //øÏÀŸ≈≈–Ú
    void quick_sort() {
        init();
        quick_sort(0, n - 1);
        cout << "øÏÀŸ≈≈–Ú£∫ ";
        output();
    }
    int partition(const int& low, const int& high) {
        int i = low;
        int j = high;
        int key = a[i];
        while (i != j) {
            while (i != j && a[j] >= key) --j;
            a[i] = a[j];
            while (i != j && a[i] <= key) ++i;
            a[j] = a[i];
        }
        a[i] = key;
        return i;
    }
    void quick_sort(const int& low, const int& high) {
        if (low < high) {
            int temp = partition(low, high);
            quick_sort(low, temp - 1);
            quick_sort(temp + 1, high);
        }
    }
};

int main() {
    Sort sort;
    while (true) {
        cout << "≈≈–Ú" << endl;
        cout << "1 —°‘Ò≈≈–Ú" << endl;
        cout << "2 √∞≈›≈≈–Ú" << endl;
        cout << "3 À´√∞≈›≈≈–Ú" << endl;
        cout << "4 ÷±Ω”≤Â»Î≈≈–Ú" << endl;
        cout << "5 ’€∞Î≤Â»Î≈≈–Ú" << endl;
        cout << "6 µ›πÈ≤Â»Î≈≈–Ú" << endl;
        cout << "7 πÈ≤¢≈≈–Ú" << endl;
        cout << "8 πÈ≤¢≤Â»Î≈≈–Ú" << endl;
        cout << "9 øÏÀŸ≈≈–Ú" << endl;
        cout << "0 ÕÀ≥ˆ" << endl;
        int choose;
        cout << "«Î—°‘Ò£∫ ";
        cin >> choose;
        if (choose == 0) break;
        switch (choose) {
            case 1:
                sort.choose_sort();
                break;
            case 2:
                sort.bubble_sort();
                break;
            case 3:
                sort.double_bubble_sort();
                break;
            case 4:
                sort.straight_insert_sort();
                break;
            case 5:
                sort.insert_sort();
                break;
            case 6:
                sort.insert_sort_digui();
                break;
            case 7:
                sort.merge_sort();
                break;
            case 8:
                sort.merge_insert_sort();
                break;
            case 9:
                sort.quick_sort();
                break;
            default:
                cout << " ‰»Î¥ÌŒÛ" << endl;
                break;
        }
        system("pause");
        system("cls");
    }
    return 0;
}