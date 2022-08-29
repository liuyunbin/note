#include<iostream>

using namespace std;

class inversion
{
private:

	int* a;
	int n;
	int count;

public:

	inversion()
	{
		n = 10;
		count = 0;
		a = new int[n];
		for (int i = 0; i != n; ++i)
			a[i] = n - i;
	}

	void merge(const int& low, const int& mid, const int& high)
	{
		int* p = new int[n];
		int i = low;
		int j = mid + 1;
		int k = 0;
		while (i != mid + 1 && j != high + 1)
		{
			if (a[i] < a[j])
				p[k++] = a[i++];
			else
			{
				p[k++] = a[j++];
				count += mid - i + 1;
			}
		}
		while (i != mid + 1)
			p[k++] = a[i++];
		while (j != high + 1)
			p[k++] = a[j++];
		for (i = low; i != high + 1; ++i)
			a[i] = p[i - low];
		delete[] p;
	}

	void merge_sort(const int& low, const int& high)
	{
		if (low < high)
		{
			int mid = (low + high) / 2;
			merge_sort(low, mid);
			merge_sort(mid + 1, high);
			merge(low, mid, high);
		}
	}

	int count_number()
	{
		merge_sort(0, n - 1);
		return count;
	}
};

int main()
{
	inversion in;
	cout << in.count_number() << endl;

	return 0;
}