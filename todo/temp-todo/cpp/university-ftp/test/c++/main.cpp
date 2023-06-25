

#include <iostream>
using namespace std;
struct node {
    int a;
    node* next;
};
node* creat() {
    int i;
    node* head = NULL;
    cin >> i;
    while (i != 11) {
        node* p = new node;
        p->a = i;
        p->next = head;
        head = p;
        cin >> i;
    }

    return head;
}
void output(node* head) {
    node* p = head;
    while (p != NULL) {
        cout << p->a << "   ";
        p = p->next;
    }
}
int main() {
    node* h = NULL;
    output(creat());
    return 0;
}
