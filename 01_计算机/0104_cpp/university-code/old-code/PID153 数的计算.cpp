#include<iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int* a = new int[n + 1];
	a[0] = 0;
	a[1] = 1;
	for (int i = 2; i != n + 1; ++i)
	{
		a[i] = 1;
		for (int j = 1; j != i / 2 + 1; ++j)
			a[i] += a[j];
	}
	cout << a[n] << endl;
	return 0;
}