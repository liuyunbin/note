#include<iostream>
#include<stack>

using namespace std;

//比较运算符优先级
bool  compare(const stack<char>& op, const char& b)
{
	char a = op.top();
	int i = 1;
    switch (a)
    {
    case '*':
    case '/': i = 3; break;
    case '+':
    case '-': i = 2; break;
    }
	int j = 1;
    switch(b)
    {
    case '*':
    case '/': j = 3; break;
    case '+':
    case '-': j = 2; break;
    }

    return  i>=j;
}

//计算
void count(stack<double>& number, stack<char>& op)
{
	double two = number.top();
	number.pop();
	double one = number.top();
	number.pop();
	char c = op.top();
	op.pop();
	switch(c)
	{
	case '+': number.push(one + two); break;
	case '-': number.push(one - two); break;
	case '*': number.push(one * two); break;
	case '/': number.push(one / two); break;
	}
}

int main()
{
	stack<double>  number;
    stack<char>    op;
    op.push('#');
    cout << "请输入表达式，以=结束" << endl;
	while (cin.peek() == ' ')
		cin.get();
	char c = cin.peek();
    while (c != '=')
    {
		if (c >= '0' && c <= '9')
        {
			double m;
			cin >> m;
	        number.push(m);
        }
        else
        {
		    cin >> c;
			switch (c)
			{
			case '(':
				op.push(c);
				break;

			case ')': 
				while (op.top() != '(')
					count(number, op);
				op.pop();
				break;

			default: 
				while (compare(op, c))
					count(number, op);
				op.push(c); 
				break;

			}
		}
		while (cin.peek() == ' ')
			cin.get();
		c = cin.peek();
	}

	while (op.top() != '#')
		count(number, op);

    cout << number.top() << endl;

    return 0;
}