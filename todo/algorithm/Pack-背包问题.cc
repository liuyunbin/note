#include <iostream>

using namespace std;

class Pack {
   private:
    int money;            //金钱数
    int money_first;      //第一种代价
    int money_second;     //第二种代价
    int count;            //物品数
    int* expense;         //费用
    int* expense_first;   //第一种费用
    int* expense_second;  //第二种费用
    int* value;           //价值
    int* benefit;
    int* max_count;  //最多使用次数
    int number;      //组元素个数 ,主件，附件

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
        cout << "P01 01背包问题：" << endl << endl;
        cout << "请输入金钱总数： ";
        cin >> money;
        cout << "请输入物品总数： ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "请输入第" << i + 1 << "件物品的价格和价值： ";
            cin >> expense[i] >> value[i];
        }
        for (int i = 0; i != count; ++i) zero_one_pack(expense[i], value[i]);
        cout << "最高价值：" << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        benefit = 0;
        expense = 0;
        value = 0;
    }

    void P02() {
        cout << "P02 完全背包问题：" << endl << endl;
        cout << "请输入金钱总数： ";
        cin >> money;
        cout << "请输入物品总数： ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "请输入第" << i + 1 << "件物品的费用和价值： ";
            cin >> expense[i] >> value[i];
        }
        for (int i = 0; i != count; ++i) complete_pack(expense[i], value[i]);
        cout << "最高价值：" << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        benefit = 0;
        expense = 0;
        value = 0;
    }

    //金钱完全用完
    void P022() {
        cout << "P022 完全背包问题，金钱完全用完：" << endl << endl;
        cout << "请输入金钱总数： ";
        cin >> money;
        cout << "请输入物品总数： ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "请输入第" << i + 1 << "件物品的费用和价值： ";
            cin >> expense[i] >> value[i];
        }
        for (int i = 0; i != count; ++i) {
            for (int j = expense[i]; j != money + 1; ++j) {
                if (benefit[j - expense[i]] != 0 || j - expense[i] == 0)
                    benefit[j] =
                        max(benefit[j], benefit[j - expense[i]] + value[i]);
            }
        }
        cout << "最高价值：" << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        benefit = 0;
        expense = 0;
        value = 0;
    }

    void P03() {
        cout << "P03 多重背包问题" << endl << endl;
        cout << "请输入金钱总数： ";
        cin >> money;
        cout << "请输入物品总数： ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        cout << "最多使用次数： ";
        int max_count;  //最多使用次数
        cin >> max_count;
        for (int i = 0; i != count; ++i) {
            cout << "请输入第" << i + 1 << "件物品的价格和价值: ";
            cin >> expense[i] >> value[i];
        }
        for (int i = 0; i != count; ++i)
            multiple_pack(expense[i], value[i], max_count);
        cout << "最高价值： " << benefit[money] << endl;
        delete[] benefit;
        delete[] expense;
        delete[] value;
        benefit = 0;
        expense = 0;
        value = 0;
    }

    void P04() {
        cout << "P04 混合三种背包问题：" << endl << endl;
        cout << "请输入金钱总数： ";
        cin >> money;
        cout << "请输入物品总数： ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        max_count = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "请输入第" << i + 1
                 << "件物品的价格和价值和使用次数（-1 代表无数）： ";
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
        cout << "最高价值： " << benefit[money] << endl;
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
        cout << "P05 二维费用的背包问题：" << endl << endl;
        cout << "请输入第一种代价： ";
        cin >> money_first;
        cout << "请输入第二种代价： ";
        cin >> money_second;
        cout << "请输入物品总数： ";
        cin >> count;
        int** benefit = new int*[money_first + 1];
        for (int i = 0; i != money_first + 1; ++i)
            benefit[i] = new int[money_second + 1]();
        expense_first = new int[count];
        expense_second = new int[count];
        value = new int[count];
        for (int i = 0; i != count; ++i) {
            cout << "请输入第" << i + 1
                 << "件物品的第一种代价，第二种代价和价值： ";
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
        cout << "最大价值： " << benefit[money_first][money_second] << endl;
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
        cout << "P06 分组的背包问题：" << endl << endl;
        cout << "请输入金钱总数： ";
        cin >> money;
        cout << "请输入组数： ";
        cin >> count;
        benefit = new int[money + 1]();
        for (int i = 1; i != count + 1; ++i) {
            cout << "请输入第 " << i << "组的物品数： ";
            cin >> number;
            expense = new int[number];
            value = new int[number];
            for (int j = 0; j != number; ++j) {
                cout << "请输入第" << i << "组第" << j + 1
                     << "件物品的价格和价值： ";
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
        cout << "最大价值： " << benefit[money] << endl;
        delete[] benefit;
        benefit = 0;
    }

    void P07() {
        cout << "P07 有依赖的背包问题： " << endl << endl;
        cout << "请输入金钱总数： ";
        cin >> money;
        cout << "请输入物品总数： ";
        cin >> count;
        benefit = new int[money + 1]();
        expense = new int[count];
        value = new int[count];
        int(*a)[3] = new int[count + 1][3]();
        int(*b)[3] = new int[count + 1][3]();
        for (int i = 1; i != count + 1; ++i) {
            cout << "请输入第" << i << "件物品的价格， 价值和主件附件： ";
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
        cout << "最大价值： " << benefit[money] << endl;
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
        cout << "背包问题： " << endl;
        cout << "1 P01 01背包问题：" << endl;
        cout << "2 P02 完全背包问题：" << endl;
        cout << "3 P03 多重背包问题：" << endl;
        cout << "4 P04 混合三种背包问题：" << endl;
        cout << "5 P05 二位费用的背包问题：" << endl;
        cout << "6 P06 分组的背包问题：" << endl;
        cout << "7 P07 有依赖的背包问题：" << endl;
        cout << "8 P022 完全背包问题，金钱完全用完" << endl;
        cout << "0 退出：" << endl;
        cout << "请选择：" << endl;
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
                cout << "输入错误，请重新输入：" << endl;
                break;
        }
        system("pause");
        system("cls");
    }

    return 0;
}