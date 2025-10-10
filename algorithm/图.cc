#include <iomanip>
#include <iostream>

#include "Queue.h"
#include "Stack.h"

using namespace std;

class Graph {
   private:
    char* vertex;
    int** a;
    int number_vertex;
    int number_edge;

    void input_undi_graph_array() {
        cout << "������������ߵ����˵㣺 " << endl;
        for (int i = 0; i != number_edge; ++i) {
            char c, c1;
            cin >> c >> c1;
            int x = get_char_number(c);
            int y = get_char_number(c1);
            if (y >= 0 && y < number_vertex && x >= 0 && x < number_vertex &&
                x != y)
                a[x][y] = a[y][x] = 1;
        }
    }

    void input_undi_network_array() {
        cout << "������������ߵ����˵�, ��Ȩֵ�� " << endl;
        for (int i = 0; i != number_edge; ++i) {
            char c, c1;
            cin >> c >> c1;
            int x = get_char_number(c);
            int y = get_char_number(c1);
            if (y >= 0 && y < number_vertex && x >= 0 && x < number_vertex &&
                x != y)
                cin >> a[x][y];
            a[y][x] = a[x][y];
        }
    }

    void input_graph_array() {
        cout << "������������ߵ����˵�: " << endl;
        for (int i = 0; i != number_edge; ++i) {
            char c, c1;
            cin >> c >> c1;
            int x = get_char_number(c);
            int y = get_char_number(c1);
            if (y >= 0 && y < number_vertex && x >= 0 && x < number_vertex &&
                x != y)
                a[x][y] = 1;
        }
    }

    void input_network_array() {
        cout << "������������ߵ����˵�, ��Ȩֵ�� " << endl;
        for (int i = 0; i != number_edge; ++i) {
            char c, c1;
            cin >> c >> c1;
            int x = get_char_number(c);
            int y = get_char_number(c1);
            if (y >= 0 && y < number_vertex && x >= 0 && x < number_vertex &&
                x != y)
                cin >> a[x][y];
        }
    }

   public:
    Graph() : a(0), vertex(0), number_vertex(0), number_edge(0) {}

    int get_char_number(const char& c) {
        int j = 0;
        while (j != number_vertex && vertex[j] != c) ++j;
        return j;
    }

    void creat() {
        cout << "�������ͱߵĸ����� ";
        cin >> number_vertex >> number_edge;
        vertex = new char[number_vertex];
        cout << "���������������Է��� ";
        for (int i = 0; i != number_vertex; ++i) cin >> vertex[i];
        a = new int*[number_vertex]();
        for (int i = 0; i != number_vertex; ++i)
            a[i] = new int[number_vertex]();
    }

    //����ͼ
    void creat_undi_graph_array() {
        creat();
        input_undi_graph_array();
    }

    //������
    void creat_undi_graph_network_array() {
        creat();
        input_undi_network_array();
    }

    //����ͼ
    void creat_graph_array() {
        creat();
        input_graph_array();
    }

    //������
    void creat_network_array() {
        creat();
        input_network_array();
    }

    //�����������
    void breadth_first_search_queue() {
        bool* visit = new bool[number_vertex]();
        int count = 0;
        for (int i = 0; count != number_vertex; ++i) {
            if (visit[i] == false) {
                Queue<int> qu;
                cout << setw(3) << vertex[i];
                qu.push(i);
                visit[i] = true;
                ++count;
                while (!qu.empty() && count != number_vertex) {
                    int j = qu.pop();
                    for (int k = 0;
                         k != number_vertex && count != number_vertex; ++k) {
                        if (visit[k] == false && a[j][k] > 0) {
                            cout << setw(3) << vertex[k];
                            qu.push(k);
                            visit[k] = true;
                            ++count;
                        }
                    }
                }
            }
        }
        cout << endl;
        delete[] visit;
    }

    //�����������
    void depth_first_search() {
        bool* visit = new bool[number_vertex]();
        int count = 0;
        for (int i = 0; count != number_vertex; ++i) {
            if (visit[i] == false) {
                cout << setw(3) << vertex[i];
                visit[i] = true;
                ++count;
                depth_first_search(i, visit, count);
            }
        }
        cout << endl;
    }
    void depth_first_search(const int& i, bool*& visit, int& count) {
        for (int j = 0; j != number_vertex && count != number_vertex; ++j) {
            if (visit[j] == false && a[i][j] > 0) {
                cout << setw(3) << vertex[j];
                visit[j] = true;
                ++count;
                depth_first_search(j, visit, count);
            }
        }
    }

    void depth_first_search_stack() {
        bool* visit = new bool[number_vertex]();
        int count = 0;
        for (int i = 0; count != number_vertex; ++i) {
            if (visit[i] == false) {
                Stack<int> st;
                cout << setw(3) << vertex[i];
                st.push(i);
                visit[i] = true;
                ++count;
                while (!st.empty() && count == number_vertex) {
                    int j = st.pop();
                    for (int k = 0;
                         k != number_vertex && count != number_vertex; ++k) {
                        if (visit[k] == false && a[j][k] > 0) {
                            st.push(k);
                            cout << setw(3) << vertex[k];
                            visit[k] = true;
                            ++count;
                            break;
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    ~Graph() {
        delete[] vertex;
        for (int i = 0; i != number_vertex; ++i) delete[] a[i];
        delete[] a;
    }
};

int main() {
    Graph graph;
    int choose_first = 1;
    while (choose_first) {
        cout << "1 ����ͼ��" << endl;
        cout << "2 ����ͼ��" << endl;
        cout << "3 ��������" << endl;
        cout << "4 ��������" << endl;
        cout << "0 �˳��� " << endl;
        cout << "��ѡ�� �� ";
        cin >> choose_first;
        switch (choose_first) {
            case 1:
                graph.creat_undi_graph_array();
                break;
            case 2:
                graph.creat_graph_array();
                break;
            case 3:
                graph.creat_undi_graph_network_array();
                break;
            case 4:
                graph.creat_network_array();
                break;
        }

        cout << "1 �������������" << endl;
        cout << "2 ��ȵݹ�����������" << endl;
        cout << "3 ��ȷǵݹ�����������" << endl;
        cout << "0 �˳�" << endl;
        int choose_second = choose_first;
        while (choose_second) {
            cout << "��ѡ�� �� ";
            cin >> choose_second;
            switch (choose_second) {
                case 1:
                    cout << setw(25) << "������������� ";
                    graph.breadth_first_search_queue();
                    break;
                case 2:
                    cout << setw(25) << "��ȵݹ����������� ";
                    graph.depth_first_search();
                    break;
                case 3:
                    cout << setw(25) << "��ȷǵݹ����������� ";
                    graph.depth_first_search_stack();
                    break;
            }
        }
        system("pause");
        system("cls");
    }
    return 0;
}