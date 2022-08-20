#ifndef c_Stack
#define c_Stack

#include<iostream>
#include<iomanip>

using namespace std;

template<typename T>
class Stack
{
private:

	T* base;
	int top;
	int init_max;
	int increment;
	
public:

	Stack(const int& init_max = 100, const int& increment = 50)
	{
		this->init_max = init_max;
		this->increment = increment;
		base = new T[init_max]();
		top = 0;
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

	bool empty() const
	{
		return top == 0;
	}

	int size() const
	{
		return top;
	}

	T get_top() const
	{
		return base[(top - 1 + init_max) % init_max];
	}

	void push(const T& data)
	{
		if (top == init_max - 1)
		{
			T* new_base = new T[init_max + increment]();
			for (int i = 0; i != top; ++i)
				new_base[i] = base[i];
			init_max += increment;
			delete[] base;
			base = new_base;
		}
		base[top++] = data;
	}

	T pop()
	{
		if (top != 0)
			return base[--top];
		return 0;
	}

	void output() const
	{
		for (int i = 0; i != top; ++i)
			cout << setw(5) << base[i];
		cout << endl;
	}

};

#endif