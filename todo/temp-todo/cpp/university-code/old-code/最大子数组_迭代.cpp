#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    int a[16] = {13, -3, -25, 20, -3,  -16, -23, 18,
                 20, -7, 12,  -5, -22, 15,  -4,  7};
    int sum = 0, low = 0, high = 0;
    int max_sum = 0, max_low = 0, max_high = 0;
    for (int i = 0; i != 16; ++i) {
        sum += a[i];
        high = i;
        if (sum < 0) {
            sum = 0;
            low = i + 1;
        }
        if (sum > max_sum) {
            max_sum = sum;
            max_low = low;
            max_high = high;
        }
    }
    for (int i = max_low; i != max_high + 1; ++i) cout << setw(5) << a[i];
    cout << endl << max_sum << endl;

    return 0;
}