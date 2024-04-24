#include <iostream>

#include "Stack.h"

using namespace std;

void conversion(int m, const int& n, Stack<char>& st) {
    while (m != 0) {
        if (m % n < 10)
            st.push('0' + m % n);
        else
            st.push('a' + (m % n) - 10);
        m /= n;
    }
}

void output(Stack<char>& st) {
    while (!st.empty()) cout << st.pop();
    cout << endl;
}

int main() {
    Stack<char> st;
    int n;
    cout << "输入要转换的进制： ";
    cin >> n;
    int m;
    cout << "输入要转换的数：  ";
    cin >> m;
    conversion(m, n, st);
    output(st);

    return 0;
}