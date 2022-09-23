
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    cout << fixed << setprecision(10);

#if 0
    int n = 22;
    cout << hex << n << endl;
    cout << showbase;
    cout << hex << n << endl;
#endif

#if 0
    cout << boolalpha;
    cout << false << endl;
    cout << true << endl;
#endif


    double x = 12345009.1234500;
    cout << x << endl;

    return 0;
}
