#include <iostream>

using namespace std;

class Pack {
   private:
    int money;            //��Ǯ��
    int money_first;      //��һ�ִ���
    int money_second;     //�ڶ��ִ���
    int count;            //��Ʒ��
    int* expense;         //����
    int* expense_first;   //��һ�ַ���
    int* expense_second;  //�ڶ��ַ���
    int* value;           //��ֵ
    int* benefit;
    int* max_count;  //���ʹ�ô���
    int number;      //��Ԫ�ظ��� ,����������

   public:
    Pack()
        : money(0),
          money_first(0),
          money_second(0),
          count(0),
          expense(0),
          expense_first(0),
          expense_second(0),
          value(0),
          benefit(0),
          max_count(0),
          number(0) {}

    int max(const int& x, const int& y) const { return x > y ? x : y; }

    int min(const int& x, const int& y) const { return x > y ? y : x; }

    void zero_one_pack(const int& expense, const int& value) {
        for (int j = money; j > expense - 1; --j)
            benefit[j] = max(benefit[j], benefit[j - expense] + value);
    }

    void complete_pack(const int& expense, const int& value) {
        for (int j = expense; j < money + 1; ++j)
            benefit[j] = max(benefit[j], benefit[j - expense] + value);
    }

    void multiple_pack(const int& expense, const int& value, int max_count) {
        max_count = min(max_count, money / expense);
        for (int j = 1; j < max_count + 1; max_count -= j, j *= 2) {
            for (int k = money; k != j * expense - 1; --k)
                benefit[k] =
                    max(benefit[k], benefit[k - j * expense] + j * value);
        }
    }

    void P01() {
        cout << "P01 01�������⣺" << endl << endl;
        cout << "�������Ǯ������ ";
        cin >> money;
        cout << "��������Ʒ������ ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "�������" << i + 1 << "����Ʒ�ļ۸�ͼ�ֵ�� ";
            cin >> expense[i] >> value[i];
        }
        for (int i = 0; i != count; ++i) zero_one_pack(expense[i], value[i]);
        cout << "��߼�ֵ��" << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        benefit = 0;
        expense = 0;
        value = 0;
    }

    void P02() {
        cout << "P02 ��ȫ�������⣺" << endl << endl;
        cout << "�������Ǯ������ ";
        cin >> money;
        cout << "��������Ʒ������ ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "�������" << i + 1 << "����Ʒ�ķ��úͼ�ֵ�� ";
            cin >> expense[i] >> value[i];
        }
        for (int i = 0; i != count; ++i) complete_pack(expense[i], value[i]);
        cout << "��߼�ֵ��" << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        benefit = 0;
        expense = 0;
        value = 0;
    }

    //��Ǯ��ȫ����
    void P022() {
        cout << "P022 ��ȫ�������⣬��Ǯ��ȫ���꣺" << endl << endl;
        cout << "�������Ǯ������ ";
        cin >> money;
        cout << "��������Ʒ������ ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "�������" << i + 1 << "����Ʒ�ķ��úͼ�ֵ�� ";
            cin >> expense[i] >> value[i];
        }
        for (int i = 0; i != count; ++i) {
            for (int j = expense[i]; j != money + 1; ++j) {
                if (benefit[j - expense[i]] != 0 || j - expense[i] == 0)
                    benefit[j] =
                        max(benefit[j], benefit[j - expense[i]] + value[i]);
            }
        }
        cout << "��߼�ֵ��" << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        benefit = 0;
        expense = 0;
        value = 0;
    }

    void P03() {
        cout << "P03 ���ر�������" << endl << endl;
        cout << "�������Ǯ������ ";
        cin >> money;
        cout << "��������Ʒ������ ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        cout << "���ʹ�ô����� ";
        int max_count;  //���ʹ�ô���
        cin >> max_count;
        for (int i = 0; i != count; ++i) {
            cout << "�������" << i + 1 << "����Ʒ�ļ۸�ͼ�ֵ: ";
            cin >> expense[i] >> value[i];
        }
        for (int i = 0; i != count; ++i)
            multiple_pack(expense[i], value[i], max_count);
        cout << "��߼�ֵ�� " << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        benefit = 0;
        expense = 0;
        value = 0;
    }

    void P04() {
        cout << "P04 ������ֱ������⣺" << endl << endl;
        cout << "�������Ǯ������ ";
        cin >> money;
        cout << "��������Ʒ������ ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        max_count = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "�������" << i + 1
                 << "����Ʒ�ļ۸�ͼ�ֵ��ʹ�ô�����-1 ������������ ";
            cin >> expense[i] >> value[i] >> max_count[i];
        }
        for (int i = 0; i != count; ++i) {
            switch (max_count[i]) {
                case 1:
                    zero_one_pack(expense[i], value[i]);
                    break;
                case -1:
                    complete_pack(expense[i], value[i]);
                    break;
                default:
                    multiple_pack(expense[i], value[i], max_count[i]);
                    break;
            }
        }
        cout << "��߼�ֵ�� " << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        delete[] max_count;
        benefit = 0;
        expense = 0;
        value = 0;
        max_count = 0;
    }

    void P05() {
        cout << "P05 ��ά���õı������⣺" << endl << endl;
        cout << "�������һ�ִ��ۣ� ";
        cin >> money_first;
        cout << "������ڶ��ִ��ۣ� ";
        cin >> money_second;
        cout << "��������Ʒ������ ";
        cin >> count;
        int** benefit = new int*[money_first + 1];
        for (int i = 0; i != money_first + 1; ++i)
            benefit[i] = new int[money_second + 1]();
        expense_first = new int[count];
        expense_second = new int[count];
        value = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "�������" << i + 1
                 << "����Ʒ�ĵ�һ�ִ��ۣ��ڶ��ִ��ۺͼ�ֵ�� ";
            cin >> expense_first[i] >> expense_second[i] >> value[i];
        }
        for (int i = 0; i != count; ++i) {
            for (int j = money_first; j > expense_first[i] - 1; --j) {
                for (int k = money_second; k > expense_second[i] - 1; --k)
                    benefit[j][k] = max(
                        benefit[j][k],
                        benefit[j - expense_first[i]][k - expense_second[i]] +
                            value[i]);
            }
        }
        cout << "����ֵ�� " << benefit[money_first][money_second] << endl;
        for (int i = 0; i != money_first + 1; ++i) {
            delete[] benefit[i];
            benefit[i] = 0;
        }
        delete[] benefit;
        delete[] expense_first;
        delete[] expense_second;
        delete[] value;
        benefit = 0;
        expense_first = 0;
        expense_second = 0;
        value = 0;
    }

    void P06() {
        cout << "P06 ����ı������⣺" << endl << endl;
        cout << "�������Ǯ������ ";
        cin >> money;
        cout << "������������ ";
        cin >> count;
        benefit = new int[money + 1]();
        for (int i = 1; i != count + 1; ++i) {
            cout << "������� " << i << "�����Ʒ���� ";
            cin >> number;
            expense = new int[number];
            value = new int[number];
            for (int j = 0; j != number; ++j) {
                cout << "�������" << i << "���" << j + 1
                     << "����Ʒ�ļ۸�ͼ�ֵ�� ";
                cin >> expense[j] >> value[j];
            }
            for (int k = money; k != 0; --k) {
                for (int j = 0; j != number; ++j) {
                    if (k >= expense[j])
                        benefit[k] =
                            max(benefit[k], benefit[k - expense[j]] + value[j]);
                }
            }
            delete[] expense;
            delete[] value;
            expense = 0;
            value = 0;
        }
        cout << "����ֵ�� " << benefit[money] << endl;
        delete[] benefit;
        benefit = 0;
    }

    void P07() {
        cout << "P07 �������ı������⣺ " << endl << endl;
        cout << "�������Ǯ������ ";
        cin >> money;
        cout << "��������Ʒ������ ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        int(*a)[3] = new int[count + 1][3]();
        int(*b)[3] = new int[count + 1][3]();
        for (int i = 1; i != count + 1; ++i) {
            cout << "�������" << i << "����Ʒ�ļ۸� ��ֵ������������ ";
            cin >> expense[i - 1] >> value[i - 1] >> number;
            if (number == 0) {
                a[i][0] = expense[i - 1];
                b[i][0] = value[i - 1] * expense[i - 1];
            } else {
                if (a[number][1] == 0) {
                    a[number][1] = expense[i - 1];
                    b[number][1] = value[i - 1] * expense[i - 1];
                } else {
                    a[number][2] = expense[i - 1];
                    b[number][2] = value[i - 1] * expense[i - 1];
                }
            }
        }

        for (int i = 1; i != count + 1; ++i) {
            if (a[i][0] != 0) {
                for (int j = money; j != a[i][0]; --j) {
                    benefit[j] =
                        max(benefit[j], benefit[j - a[i][0]] + b[i][0]);
                    if (j >= a[i][0] + a[i][1])
                        benefit[j] =
                            max(benefit[j], benefit[j - a[i][0] - a[i][1]] +
                                                b[i][0] + b[i][1]);
                    if (j >= a[i][0] + a[i][2])
                        benefit[i] =
                            max(benefit[j], benefit[j - a[i][0] - a[i][2]] +
                                                b[i][0] + b[i][2]);
                    if (j >= a[i][0] + a[i][1] + a[i][2])
                        benefit[j] =
                            max(benefit[j],
                                benefit[j - a[i][0] - a[i][1] - a[i][2]] +
                                    b[i][0] + b[i][1] + b[i][2]);
                }
            }
        }
        cout << "����ֵ�� " << benefit[money] << endl;
        delete[] benefit;
        delete[] a;
        delete[] b;
        delete[] expense;
        delete[] value;
        benefit = 0;
        a = 0;
        b = 0;
        expense = 0;
        value = 0;
    }
};

int main() {
    Pack pack;
    while (true) {
        cout << "�������⣺ " << endl;
        cout << "1 P01 01�������⣺" << endl;
        cout << "2 P02 ��ȫ�������⣺" << endl;
        cout << "3 P03 ���ر������⣺" << endl;
        cout << "4 P04 ������ֱ������⣺" << endl;
        cout << "5 P05 ��λ���õı������⣺" << endl;
        cout << "6 P06 ����ı������⣺" << endl;
        cout << "7 P07 �������ı������⣺" << endl;
        cout << "8 P022 ��ȫ�������⣬��Ǯ��ȫ����" << endl;
        cout << "0 �˳���" << endl;
        cout << "��ѡ��" << endl;
        int choose;
        cin >> choose;
        if (choose == 0) break;
        switch (choose) {
            case 1:
                pack.P01();
                break;
            case 2:
                pack.P02();
                break;
            case 3:
                pack.P03();
                break;
            case 4:
                pack.P04();
                break;
            case 5:
                pack.P05();
                break;
            case 6:
                pack.P06();
                break;
            case 7:
                pack.P07();
                break;
            case 8:
                pack.P022();
                break;
            default:
                cout << "����������������룺" << endl;
                break;
        }
        system("pause");
        system("cls");
    }

    return 0;
}