#include<iostream>
#include<iomanip>
#include"Queue.h"
#include"Stack.h"

using namespace std;

class Graph
{
private:

	char* vertex;
	int** a;
	int number_vertex;
	int number_edge;

	void input_undi_graph_array()
	{
		cout << "依次输入各条边的两端点： " << endl;
		for (int i = 0; i != number_edge; ++i)
		{
			char c, c1;
			cin >> c >> c1;
			int x = get_char_number(c);
			int y = get_char_number(c1);
			if (y >= 0 && y < number_vertex && x >= 0 && x < number_vertex && x != y)
				a[x][y] = a[y][x] = 1;
		}
	}

	void input_undi_network_array()
	{
		cout << "依次输入各条边的两端点, 和权值： " << endl;
		for (int i = 0; i != number_edge; ++i)
		{
			char c, c1;
			cin >> c >> c1;
			int x = get_char_number(c);
			int y = get_char_number(c1);
			if (y >= 0 && y < number_vertex && x >= 0 && x < number_vertex && x != y)
				cin >> a[x][y];
			a[y][x] = a[x][y];
		}
	}

	void input_graph_array()
	{
		cout << "依次输入各条边的两端点: " << endl;
		for (int i = 0; i != number_edge; ++i)
		{
			char c, c1;
			cin >> c >> c1;
			int x = get_char_number(c);
			int y = get_char_number(c1);
			if (y >= 0 && y < number_vertex && x >= 0 && x < number_vertex && x != y)
				 a[x][y] = 1;
		}
	}

	void input_network_array()
	{
		cout << "依次输入各条边的两端点, 和权值： " << endl;
		for (int i = 0; i != number_edge; ++i)
		{
			char c, c1;
			cin >> c >> c1;
			int x = get_char_number(c);
			int y = get_char_number(c1);
			if (y >= 0 && y < number_vertex && x >= 0 && x < number_vertex && x != y)
				cin >> a[x][y];
		}
	}

public:

	Graph() : a(0), vertex(0), number_vertex(0), number_edge(0){}

	int get_char_number(const char& c)
	{
		int j = 0;
		while (j != number_vertex && vertex[j] != c)
			++j;
		return j;
	}

	void creat()
	{
		cout << "请输入点和边的个数： ";
		cin >> number_vertex >> number_edge;
		vertex = new char[number_vertex];
		cout << "依次输入各个点的自符： ";
		for (int i = 0; i != number_vertex; ++i)
			cin >> vertex[i];
		a = new int*[number_vertex]();
		for (int i = 0; i != number_vertex; ++i)
			a[i] = new int[number_vertex]();
	}

	//无向图
	void creat_undi_graph_array()
	{
		creat();
		input_undi_graph_array();
	}

	//无向网
	void creat_undi_graph_network_array()
	{
		creat();
		input_undi_network_array();
	}
    
	//有向图
	void creat_graph_array()
	{
		creat();
		input_graph_array();
	}

	//有向网
	void creat_network_array()
	{
		creat();
		input_network_array();
	}

	//广度优先搜索
	void breadth_first_search_queue()
	{
		bool* visit = new bool[number_vertex]();
		int count = 0;
		for (int i = 0; count != number_vertex; ++i)
		{
			if (visit[i] == false)
			{
				Queue<int> qu;
				cout << setw(3) << vertex[i];
				qu.push(i);
				visit[i] = true;
				++count;
				while (!qu.empty() && count != number_vertex)
				{
					int j = qu.pop();
					for (int k = 0; k != number_vertex && count != number_vertex; ++k)
					{
						if (visit[k] == false && a[j][k] > 0)
						{
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

	//深度优先搜索
	void depth_first_search()
	{
		bool* visit = new bool[number_vertex]();
		int count = 0;
		for (int i = 0; count != number_vertex; ++i)
		{
			if (visit[i] == false)
			{
				cout << setw(3) << vertex[i];
				visit[i] = true;
				++count;
				depth_first_search(i, visit, count);
			}
		}
		cout << endl;
	}
	void depth_first_search(const int& i, bool*& visit, int& count)
	{
		for (int j = 0; j != number_vertex && count != number_vertex; ++j)
		{
			if (visit[j] == false && a[i][j] > 0)
			{
				cout << setw(3) << vertex[j];
				visit[j] = true;
				++count;
				depth_first_search(j, visit, count);
			}
		}
	}

	void depth_first_search_stack()
	{
		bool* visit = new bool[number_vertex]();
		int count = 0;
		for (int i = 0; count != number_vertex; ++i)
		{
			if (visit[i] == false)
			{
				Stack<int> st;
				cout << setw(3) << vertex[i];
				st.push(i);
				visit[i] = true;
				++count;
				while (!st.empty() && count == number_vertex)
				{
					int j = st.pop();
					for (int k = 0; k != number_vertex && count != number_vertex; ++k)
					{
						if (visit[k] == false && a[j][k] > 0)
						{
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

	~Graph()
	{
		delete[] vertex;
		for (int i = 0; i != number_vertex; ++i)
			delete[] a[i];
		delete[] a;
	}

};

int main()
{
	Graph graph;
	int choose_first = 1;
	while (choose_first)
	{
		cout << "1 无向图：" << endl;
		cout << "2 有向图：" << endl;
		cout << "3 无向网：" << endl;
		cout << "4 有向网：" << endl;
		cout << "0 退出： " << endl;
		cout << "请选择 ： ";
		cin >> choose_first;
		switch (choose_first)
		{
		case 1: graph.creat_undi_graph_array(); break;
		case 2: graph.creat_graph_array(); break;
		case 3: graph.creat_undi_graph_network_array(); break;
		case 4: graph.creat_network_array(); break;
		}

		cout << "1 广度优先搜索：" << endl;
		cout << "2 深度递归优先搜索：" << endl;
		cout << "3 深度非递归优先搜索：" << endl;
		cout << "0 退出" << endl;
		int choose_second = choose_first;
		while (choose_second)
		{
			cout << "请选择 ： ";
			cin >> choose_second;
			switch (choose_second)
			{
			case 1:
				cout << setw(25) << "广度优先搜索： ";
				graph.breadth_first_search_queue();
				break;
			case 2:
				cout << setw(25) << "深度递归优先搜索： ";
				graph.depth_first_search();
				break;
			case 3:
				cout << setw(25) << "深度非递归优先搜索： ";
				graph.depth_first_search_stack();
				break;
			}
		}
		system("pause");
		system("cls");
	}
	return 0;
}