#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

class Mineswepper {
   private:
    int n;
    int count;
    int number;
    int game;
    int a[11][11][3];
    int x;
    int y;

   public:
    Mineswepper() { n = 11; }

    void init() {
        game = 1;
        number = 0;
        for (int i = 0; i != 11; ++i)
            for (int j = 0; j != 11; ++j)
                a[i][j][0] = a[i][j][1] = a[i][j][2] = 0;
        cout << "�������׵ĸ�����(����10��С��30) ��  ";
        while (1) {
            cin >> count;
            if (count >= 10 && count <= 30) break;
            cout << "�����������������" << endl;
        }
        system("cls");
        //����
        srand(int(time(0)));
        for (int i = 0; i != count;) {
            int x = rand() % (n - 2) + 1;
            int y = rand() % (n - 2) + 1;
            if (a[x][y][0] == 0) {
                a[x][y][0] = 1;
                ++i;
            }
        }
        //ͳ���׵ĸ���
        for (int i = 1; i != n - 1; ++i)
            for (int j = 1; j != n - 1; ++j)
                a[i][j][1] = a[i - 1][j - 1][0] + a[i - 1][j][0] +
                             a[i - 1][j + 1][0] + a[i][j - 1][0] +
                             a[i][j + 1][0] + a[i + 1][j - 1][0] +
                             a[i + 1][j][0] + a[i + 1][j + 1][0];
    }

    void search(const int& x, const int& y) {
        a[x][y][2] = 1;
        if (a[x][y][1] == 0) {
            if (x - 1 != 0 && y - 1 != 0 && a[x - 1][y - 1][2] != 1)
                search(x - 1, y - 1);
            if (x - 1 != 0 && a[x - 1][y][2] != 1) search(x - 1, y);
            if (x - 1 != 0 && y + 1 != n - 1 && a[x - 1][y + 1][2] != 1)
                search(x - 1, y + 1);
            if (y - 1 != 0 && a[x][y - 1][2] != 1) search(x, y - 1);
            if (y + 1 != n - 1 && a[x][y + 1][2] != 1) search(x, y + 1);
            if (x + 1 != n - 1 && y - 1 != 0 && a[x + 1][y - 1][2] != 1)
                search(x + 1, y - 1);
            if (x + 1 != n - 1 && a[x + 1][y][2] != 1) search(x + 1, y);
            if (x + 1 != n - 1 && y + 1 != n - 1 && a[x + 1][y + 1][2] != 1)
                search(x + 1, y + 1);
        }
    }

    void print() {
        system("cls");
        cout << "�׵ĸ�����" << count << "     �Ѵ�" << number << "��"
             << endl;
        for (int i = 1; i != n - 1; ++i) {
            for (int j = 1; j != n - 1; ++j) {
                switch (a[i][j][2]) {
                    case 0:
                        cout << setw(5) << "��";
                        break;
                    case 1:
                        if (a[i][j][1] != 0)
                            cout << setw(5) << a[i][j][1];
                        else
                            cout << setw(5) << ' ';
                        break;
                    case 2:
                        cout << setw(5) << "!";
                        break;
                    case 3:
                        cout << setw(5) << "?";
                        break;
                }
            }
            cout << endl << ' ';
            for (int j = 1; j != n - 1; ++j) {
                if (a[i][j][2] != 1)
                    cout << ' ' << i << ',' << j << ' ';
                else
                    cout << setw(5) << ' ';
            }
            cout << endl;
        }
    }

    void pd() {
        while (1) {
            cout << "�������������꣺ ";
            cin >> x >> y;
            if (x > 0 && x < 10 && y > 0 && y < 10 && a[x][y][2] != 1) break;
            cout << "�����������������" << endl;
        }
        cout << "1��ʾ�򿪣�2��ʾ���ף�3��ʾ������  ��ѡ��  ";
        while (1) {
            int choose;
            cin >> choose;
            switch (choose) {
                case 1:
                    if (a[x][y][0] == 0)
                        search(x, y);
                    else
                        game = 0;
                    break;
                case 2:
                    a[x][y][2] = 2;
                    break;
                case 3:
                    a[x][y][2] = 3;
                    break;
            }
            if (choose == 1 || choose == 2 || choose == 3) break;
            cout << "�������������ѡ��" << endl;
        }
    }

    void count_number() {
        number = 0;
        for (int i = 1; i != n - 1; ++i)
            for (int j = 1; j != n - 1; ++j)
                if (a[i][j][2] == 1) ++number;
    }

    void saolei() {
        this->init();
        while (1) {
            this->print();
            this->pd();
            this->count_number();
            if (number == (n - 2) * (n - 2) + count || game == 0) break;
        }
        if (game == 1)
            cout << "��Ϸ�ɹ�������" << endl;
        else
            cout << "��Ϸʧ�ܣ�����" << endl;
        system("pause");
    }
};

int main() {
    Mineswepper sl;
    int choose = 1;
    while (1) {
        cout << "**************************************************************"
                "*****************"
             << endl;
        cout << "********************************��ӭ��ɨ����Ϸ****************"
                "*****************"
             << endl;
        cout << "**************************************************************"
                "*****************"
             << endl;
        cout << "---------------------------------1  "
                "����Ϸ-------------------------------------"
             << endl;
        cout << "---------------------------------0  "
                "�˳�---------------------------------------"
             << endl;
        cout << "��ѡ�� ";
        cin >> choose;
        if (choose == 1) sl.saolei();
        if (choose == 0) break;
        system("cls");
    }

    return 0;
}