#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    char c;
    int data;
    string st;
    int parent, lchild, rchild;
    Node(const char& c = 0, const int& data = 0)
        : c(c), data(data), st(""), parent(0), lchild(0), rchild(0) {}
};

class Huffman {
   private:
    Node* p;
    int n;

   public:
    Huffman() : p(0), n(0) {}

    void select(const int& i) {
        int lchild = 0;
        while (p[lchild].parent != 0) ++lchild;
        for (int j = lchild; j != i; ++j) {
            if (p[j].data < p[lchild].data && p[j].parent == 0) lchild = j;
        }
        int rchild = 0;
        while (p[rchild].parent != 0 || rchild == lchild) ++rchild;
        for (int j = rchild; j != i; ++j) {
            if (p[j].data < p[rchild].data && j != lchild && p[j].parent == 0)
                rchild = j;
        }
        p[i].lchild = lchild;
        p[i].rchild = rchild;
        p[lchild].parent = p[rchild].parent = i;
        p[i].data = p[lchild].data + p[rchild].data;
    }

    //�����������
    void creat_huffman_tree() {
        cout << "������ĸ����� ";
        cin >> n;
        delete[] p;
        p = new Node[2 * n - 1];
        cout << "������������ַ���Ȩ��  ";
        for (int i = 0; i != n; ++i) cin >> p[i].c >> p[i].data;
        for (int i = n; i != 2 * n - 1; ++i) select(i);
        for (int i = 0; i != n; ++i) {
            int j = i;
            int parent = p[j].parent;
            while (parent != 0) {
                if (j == p[parent].lchild)
                    p[i].st = "0" + p[i].st;
                else
                    p[i].st = "1" + p[i].st;
                j = parent;
                parent = p[j].parent;
            }
        }
    }

    //�������������
    void output() {
        for (int i = 0; i != n; ++i)
            cout << setw(5) << p[i].c << setw(5) << p[i].st << endl;
    }

    //����������
    void huffman_code() {
        cout << "����Ҫ�����ԭ��" << endl;
        string st;
        cin >> st;
        for (int i = 0; i != st.size(); ++i) {
            int j = 0;
            while (p[j].c != st[i] && j != n) ++j;
            cout << p[j].st;
        }
        cout << endl;
    }

    //����������
    void huffman_de_code() {
        cout << "����Ҫ�����ԭ��" << endl;
        string st;
        cin >> st;
        Node N = p[2 * n - 2];
        for (int i = 0; i != st.size(); ++i) {
            if (st[i] == '0')
                N = p[N.lchild];
            else
                N = p[N.rchild];
            if (N.c != 0) {
                cout << N.c;
                N = p[2 * n - 2];
            }
        }
        cout << endl;
    }
};

int main() {
    Huffman hfm;
    cout << "huffman: " << endl;
    cout << "1 �������������" << endl;
    cout << "2 ���������룺 " << endl;
    cout << "3 ���������룺 " << endl;
    cout << "0 �˳��� " << endl;
    int choose = 1;
    while (choose) {
        cout << "��ѡ�� ";
        cin >> choose;
        switch (choose) {
            case 1:
                hfm.creat_huffman_tree();
                hfm.output();
                break;
            case 2:
                hfm.huffman_code();
                break;
            case 3:
                hfm.huffman_de_code();
                break;
        }
    }

    return 0;
}