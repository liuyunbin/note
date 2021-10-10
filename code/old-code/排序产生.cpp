#include<iostream>

using namespace std;

void perm(int* &a, const int& k, const int& n)
{
	if (k == n - 1)
	{
		for (int i = 0; i != n; ++i)
			cout << a[i] << " ";
		cout << endl;
	}
	else
	{
		for (int i = k; i != n; ++i)
		{
			int temp = a[k];
			a[k] = a[i];
			a[i] = temp;

			perm(a, k + 1, n);

			temp = a[k];
			a[k] = a[i];
			a[i] = temp;
		}
	}
}

int main()
{
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i != n; ++i)
		a[i] = i + 1;
	perm(a, 0, n);

	return 0;
}