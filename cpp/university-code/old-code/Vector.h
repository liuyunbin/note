#ifndef c_Vector
#define c_Vector

#include<iostream>
#include<iomanip>

using namespace std;

template<typename T>
class Vector
{
private:

	T* base;
	int init_max;
	int increment;
	int length;

	void increase_init_max()
	{
		T* new_base = new T[init_max + increment]();
		for (int i = 0; i != length; ++i)
			new_base[i] = base[i];
		delete[] base;
		base = new_base;
		init_max += increment;
	}

	static bool init_compare(const T& t_1, const T& t_2)
	{
		return t_1 > t_2;
	}

	static bool init_equal(const T& t_1, cconst T& t_2)
	{
		return t_1 == t_2;
	}

public:

	Vector(const int& init_max = 100, const int& increment = 50)
	{
		this->init_max = init_max;
		this->increment = increment;
		base = new T[init_max]();
		length = 0;
	}

	void set_init_max(const int& init_max)
	{
		this->init_max = init_max;
		delete[] base;
		base = new T[init_max]();
	}

	void set_increment(const int& increment)
	{
		this->increment = increment;
	}

	T get_elem(const int& i) const
	{
		if (i >= 0 && i < length)
			return base[i];
		else
			return -1;
	}

	bool empty() const
	{
		return length == 0;
	}

	int size() const
	{
		return length;
	}

	T back() const
	{
		return base[(length - 1 + init_max) % init_max];
	}

	T front() const
	{
		return base[0];
	}

	void push_back(const T& data)
	{
		if (length + 1 == init_max)
			increase_init_max();
		base[length++] = data;
	}

	void push_front(const T& data)
	{
		if (length + 1 == init_max)
			increase_init_max();
		for (int i = length; i != 0; --i)
			base[i] = base[i - 1];
		base[0] = data;
		++length;
	}

	T pop_back()
	{
		if (length != 0)
			return base[--length];
		return -1;
	}

	T pop_front()
	{
		if (length != 0)
		{
			T data = base[0];
			--length;
			for (int i = 0; i != length; ++i)
				base[i] = base[i + 1];
			return data;
		}
		return -1;
	}

	Node<T>* search(const T& elem)
	{
		return search(elem, init_eaual);
	}

	Node<T>* search(const T& elem, bool(*equal)(const T& t_1, const T& t_2))
	{
		int i = 0;
		while (i != length && equal(elem, base[i]) == true)
			++i;
		if (i != length)
			return base + i;
		return 0;
	}

	void insert(Node<T>* p, const T& data)
	{
		if (p - base >= 0 && p - base < length)
		{
			if (length + 1 == init_max)
				increase_init_max();
			for (int j = length; j != p - base; --j)
				base[j] = base[j - 1];
			base[p - base] = data;
			++length;
		}
	}

	void insert(const int& elem, const T& data, bool(*equal)(const T& t_1, const T& t_2))
	{
		insert(search(elem, equal), data);
	}

	void insert(const int& elem, const T& data)
	{
		insert(search(elem), data);
	}

	T earse(Node<T>* p)
	{
		if (p - base >= 0 && p - base < length)
		{
			T data = p->data;
			--length;
			for (int j = p - base; j != length; ++j)
				base[j] = base[j + 1];
			return data;
		}
		return -1;
	}

	T earse(const int& i)
	{
		return earse(search(i));
	}

	T earse(const int& i, bool(*equal)(const T& t_1, const T& t_2))
	{
		return earse(search(i, equal));
	}


	void reverse()
	{
		for (int i = 0; i != length / 2; ++i)
		{
			T temp = base[i];
			base[i] = base[length - i - 1];
			base[length - 1 - i] = temp;
		}
	}

	void sort()
	{
		merge_sort(0, length - 1, init_compare);
	}

	void sort(bool (*compare)(const T& t_1, const T& t_2))
	{
		merge_sort(0, length - 1, compare);
	}

	void merge(const int& low, const int& mid, const int& high, bool (*compare)(const T& t_1, const T& t_2))
	{
		T* p = new T[high - low + 1];
		int i = low;
		int j = mid + 1;
		int k = 0;
		while (i != mid + 1 && j != high + 1)
		{
			if (compare(base[i], base[j]) == false)
				p[k++] = base[i++];
			else
				p[k++] = base[j++];
		}
		while (i != mid + 1)
			p[k++] = base[i++];
		while (j != high + 1)
			p[k++] = base[j++];
		for (i = low; i != high + 1; ++i)
			base[i] = p[i - low];
		delete[] p;
	}
	void merge_sort(const int& low, const int& high, bool (*compare)(const T& t_1, const T& t_2))
	{
		if (low < high)
		{
			int mid = (low + high) / 2;
			merge_sort(low, mid, compare);
			merge_sort(mid + 1, high, compare);
			merge(low, mid, high, compare);
		}
	}

	void merge(Vector<T>& ve2)
	{
		merge(ve2, init_compare);
	}

	void merge(Vector<T>& ve2, bool(*compare)(const T& t_1, const T& t_2))
	{
		while (this->length + ve2.length > init_max)
			increase_init_max();
		int i = 0;
		int j = 0;
		int k = 0;
		T* p = new T[this->length + ve2.length];
		while (i != this->length && j != ve2.length)
		{
			if (compare(base[i], ve2.base[j]) == false)
				p[k++] = base[i++];
			else
				p[k++] = ve2.base[j++];
		}
		while (i != this->length)
			p[k++] = base[i++];
		while (j != ve2.length)
			p[k++] = ve2.base[j++];
		delete[] base;
		base = p;
		this->length += ve2.length;
		delete[] ve2.base;
	}

	void output() const
	{
		for (int i = 0; i != length; ++i)
			cout << setw(5) << base[i];
		cout << endl;
	}

};

#endif