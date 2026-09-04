#include <iostream>

using namespace std;

struct Node {
    char name[20];
    int terminal_grade;
    int class_grade;
    char student_cadres;
    char western_province;
    int count;
    int money;
    Node() : money(0) {}
};

int main() {
    int n;
    cin >> n;
    Node* a = new Node[n];
    for (int i = 0; i != n; ++i) {
        int j = 0;
        while (cin.peek() != ' ' && j != 20) {
            cin >> a[i].name[j];
            ++j;
        }
        a[i].name[j] = '\0';
        cin >> a[i].terminal_grade >> a[i].class_grade >> a[i].student_cadres >>
            a[i].western_province >> a[i].count;
    }
    for (int i = 0; i != n; ++i) {
        if (a[i].terminal_grade > 80 && a[i].count > 0) a[i].money += 8000;
        if (a[i].terminal_grade > 85 && a[i].class_grade > 80)
            a[i].money += 4000;
        if (a[i].terminal_grade > 90) a[i].money += 2000;
        if (a[i].terminal_grade > 85 && a[i].western_province == 'Y')
            a[i].money += 1000;
        if (a[i].class_grade > 80 && a[i].student_cadres == 'Y')
            a[i].money += 850;
    }
    int j = 0;
    int sum = 0;
    for (int i = 0; i != n; ++i) {
        sum += a[i].money;
        if (a[i].money > a[j].money) j = i;
    }
    for (int i = 0; a[j].name[i] && i != 20; ++i) cout << a[j].name[i];
    cout << endl << a[j].money << endl << sum << endl;

    return 0;
}