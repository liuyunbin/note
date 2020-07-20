#include<iostream>
#include<iomanip>

using namespace std;

int main()
{
	int n = 5;
	cin >> n;
	int** a = new int*[n];
	for (int i = 0; i != n; ++i)
		a[i] = new int[n]();
	a[0][(n - 1) / 2] = 1;
	for (int i = 0, j = (n - 1) / 2, k = 1; k != n * n; ++k)
	{
		i = (i + n - 1) % n;
		j = (j +1) % n;
		if (a[i][j] != 0)
		{
			i = (i + 2) % n;
			j = (j + n - 1) % n;
		}
		a[i][j] = k + 1;
	}

	for (int i = 0; i != n; ++i)
	{
		for (int j = 0; j != n; ++j)
			cout << setw(5) << a[i][j];
		cout << endl;
	}

	return 0;
}