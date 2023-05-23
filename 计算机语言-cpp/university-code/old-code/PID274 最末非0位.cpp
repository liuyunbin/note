#include <iostream>

using namespace std;

int main() {
    int a[4][4] = {6, 2, 4, 8, 1, 3, 9, 7, 1, 7, 9, 3, 1, 9, 1, 9};
    int n;
    cin >> n;
    int count_2 = 0;
    int count_3 = 0;
    int count_5 = 0;
    int count_7 = 0;
    int count_9 = 0;

    for (int i = n / 2; i != 0; i /= 2) count_2 += i;
    for (int i = n / 5; i != 0; i /= 5) count_5 += i;

    for (int i = n; i != 0; i /= 2)
        for (int j = i; j != 0; j /= 5) {
            count_3 += j / 10 + (j % 10 >= 3);
            count_7 += j / 10 + (j % 10 >= 7);
            count_9 += j / 10 + (j % 10 >= 9);
        }

    int count = a[1][count_3 % 4] * a[2][count_7 % 4] * a[3][count_9 % 4];

    if (count_5 > count_2)
        count = 5;
    else if (count_2 > count_5)
        count *= a[0][(count_2 - count_5) % 4];

    cout << count % 10 << endl;

    return 0;
}