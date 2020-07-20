#include<iostream>
#include<iomanip>

using namespace std;

template<typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node(const T& data = 0, Node<T>* next = 0) : data(data), next(next){}
};

template<typename T>
class List
{

private:

	Node<T>* head;
	Node<T>* tail;

public:

	List()
	{
		head = tail = new Node<T>(0, head);
	}

	Node<T>* begin() const
	{
		return head->next;
	}

	Node<T>* end() const
	{
		return head;
	}

	T get_back() const
	{
		return tail->data;
	}

	T get_front() const
	{
		return head->next->data;
	}

	bool empty() const
	{
		return head == tail;
	}

	int size() const
	{
		int count = 0;
		for (Node<T>* p = head; p != tail; p = p->next)
			++count;
		return count;
	}

	void push_back(const T& data)
	{
		Node<T>* p = new Node<T>(data, head);
		tail->next = p;
		tail = p;
	}

	void push_front(const T& data)
	{
		Node* p = new Node(data, head->next);
		head->next = p;
		if (p->next == head)
			tail = p;
	}

	T pop_back()
	{
		if (head != tail)
		{
			T data = tail->data;
			Node<T>* p = head;
			while (p->next != tail)
				p = p->next;
			delete tail;
			tail = p;
			tail->next = head;
			return data;
		}
		return -1;
	}

	T pop_front()
	{
		if (head != tail)
		{
			Node<T>* p = head->next;
			T data = p->data;
			head->next = p->next;
			delete p;
			if (head->next == head)
				tail = head;
			return data;
		}
		return -1;
	}

	void insert(Node<T>* p, const T& data)
	{
		Node<T>* p1 = head;
		while (p1->next != head && p1->next != p)
			p1 = p1->next;
		if (p1->next == p)
		{
			Node<T>* p2 = new Node<T>(data, p);
			p1->next = p2;
		}
	}

	T earse(Node<T>* p)
	{
		Node<T>* p1 = head;
		while (p1->next != head && p1->next != p)
			p1 = p1->next;
		if (p1->next == p)
		{
			T data = p->data;
			p1->next = p->next;
			delete p;
			if (head->next == head)
				tail = head;
			return data;
		}
		return -1;
	}

	void sort()
	{
		Node<T>* p1 = head;
		while (p1->next->next != head)
		{
			Node<T>* p2 = p1->next;
			Node<T>* p3 = p1;
			while (p2->next != head)
			{
				if (p2->next->data < p3->next->data)
					p3 = p2;
				p2 = p2->next;
			}
			if (p1 != p3)
			{
				p2 = p1->next;
				p1->next = p3->next;
				p1 = p1->next;
				p3->next = p1->next;
				p1->next = p2;
			}
			else
			{
				p1 = p1->next;
			}
		}
		tail = p1->next;
	}

	void merge(List<T> li2)
	{
		Node<T>* p1 = head;
		Node<T>* p2 = head->next;
		Node<T>* p3 = li2.head->next;
		while (p2 != head && p3 != li2.head)
		{
			if (p2->data < p3->data)
			{
				p1->next = p2;
				p1 = p2;
				p2 = p2->next;
			}
			else
			{
				p1->next = p3;
				p1 = p3;
				p3 = p3->next;
			}
		}
		if (p2 != head)
		{
			p1->next = p2;
		}
		else
		{
			p1->next = p3;
			tail = li2.tail;
			tail->next = head;
		}
		delete li2.head;
	}

	void reverse()
	{
		Node<T>* p1 = head->next;
		Node<T>* p2 = p1->next;
		while (p2 != head)
		{
			Node<T>* p3 = p2->next;
			p2->next = head->next;
			head->next = p2;
			p2 = p3;
		}
		tail = p1;
		tail->next = head;
	}

	void output() const
	{
		for (Node<T>* p = head->next; p != head; p = p->next)
			cout << setw(5) << p->data ;
		cout << endl;
	}

};


int main()
{
	List<double> li;
	List<double> li2;
	for (int i = 0; i != 10; ++i)
	{
		li.push_back(10 - i);
		//li2.push_back(20 - 2 * i);
	}
	//cout << li.pop_back() << endl;
	//cout << li.pop_front() << endl;
	//cout << li.get_back() << endl << li.get_front() << endl << li.size() << endl << li.empty() << endl;
	//li.insert(li.end(), 100);
	//cout << li.earse(li.begin()) << endl << endl;
	li.sort();
	//li2.sort();
	//li.merge(li2);
	//li.reverse();
	li.output();
	cout << li.size() << endl;
	return 0;
}