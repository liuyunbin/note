#include<iostream>
#include<iomanip>
#include"Stack.h"
#include"Queue.h"

using namespace std;

struct  Node
{
	char data;
	Node* lchild;
	Node* rchild;
	Node(const char& data = 0) : data(data), lchild(0), rchild(0){}
};

class  Bin_Tree
{

private:

	Node* root;

public:

	Bin_Tree() : root(0){}

	//初始化
	void creat_bintree()
	{
		char c = cin.get();
		if (c != ' ')
		{
			root = new Node(c);
			creat_bintree(root->lchild);
			creat_bintree(root->rchild);
		}
	}
	void creat_bintree(Node*& p)
	{
		char c = cin.get();
		if (c != ' ')
		{
			p = new Node(c);
			creat_bintree(p->lchild);
			creat_bintree(p->rchild);
		}
	}

	//先序输出
	void pre_order_traverse()
	{
		pre_order_traverse(root);
	}
	void pre_order_traverse(Node* p)
	{
		if (p)
		{
			cout << setw(5) << p->data;
			pre_order_traverse(p->lchild);
			pre_order_traverse(p->rchild);
		}
	}
	
	void pre_order_traverse_stack()
	{
		Stack<Node*> st;
		if (root)
			st.push(root);
		while (!st.empty())
		{
			Node* p = st.get_top();
			st.pop();
			cout << setw(5) << p->data;
			if (p->rchild)
				st.push(p->rchild);
			if (p->lchild)
				st.push(p->lchild);
		}
	}

	//中序输出
	void in_order_traverse()
	{
		in_order_traverse(root);
	}
	void in_order_traverse(Node* p)
	{
		if (p)
		{
			in_order_traverse(p->lchild);
			cout << setw(5) << p->data;
			in_order_traverse(p->rchild);
		}
	}
	
	void in_order_traverse_stack()
	{
		Stack<Node*> st;
		Node* p = root;
		while (p || (!st.empty()))
		{
			if (p)
			{
				st.push(p);
				p = p->lchild;
			}
			else
			{
				p = st.get_top();
				st.pop();
				cout << setw(5) << p->data;
				p = p->rchild;
			}
		}
	}

	//后序序输出
	void post_order_traverse()
	{
		post_order_traverse(root);
	}
	void post_order_traverse(Node* p)
	{
		if (p)
		{
			post_order_traverse(p->lchild);
			post_order_traverse(p->rchild);
			cout << setw(5) << p->data;
		}
	}
	
	void post_order_traverse_stack()
	{
		Stack<Node*> st;
		Node* pre = 0; 
		if (root)
			st.push(root);
		while (!st.empty())
		{
			Node* cur = st.get_top();
			if ((cur->lchild == 0 && cur->rchild == 0) || pre == cur->rchild
				|| (pre == cur->lchild && cur->rchild == 0))
			{
				cout << setw(5) << cur->data;  
				st.pop();
				pre = cur;
			}
			else
			{
				if (cur->rchild)
					st.push(cur->rchild);
				if (cur->lchild)
					st.push(cur->lchild);
			}
		}
	}

	//层遍历
	void level_order_traverse_queue()
	{
		Queue<Node*> qu;
		if (root)
			qu.push(root);
		while (!qu.empty())
		{
			Node* p = qu.get_front();
			qu.pop();
			cout << setw(5) << p->data;
			if (p->lchild)
				qu.push(p->lchild);
			if (p->rchild)
				qu.push(p->rchild);
		}
	}

	//二叉树的深度
	int  length()
	{
		return length(root);
	}
	int  length(Node* p)
	{
		if (p == 0)
			return 0;
		else
			return   1 + (length(p->lchild) > length(p->rchild) ? length(p->lchild) : length(p->rchild));
	}

};


int main()
{
	Bin_Tree  tree;
	cout << "以先序输入二叉树，空格表示空树: ";
	tree.creat_bintree();
	cout << "二叉树：" << endl;
	cout << "1 先序输出" << endl;
	cout << "2 先序非递归输出" << endl;
	cout << "3 中序输出" << endl;
	cout << "4 中序非递归输出" << endl;
	cout << "5 后序输出" << endl;
	cout << "6 后序非递归输出" << endl;
	cout << "7 层遍历非递归输出" << endl;
	cout << "8 二叉树的深度" << endl;
	cout << "0 退出" << endl;
	while (true)
	{
		int choose;
		cout << endl << "请选择： ";
		cin >> choose;
		if (choose == 0)
			break;
		switch (choose)
		{
		case 1: 
			cout << setw(20) << "先序输出: " ;
			tree.pre_order_traverse(); 
			break;
		case 2:
			cout << setw(20) << "先序非递归输出: ";
			tree.pre_order_traverse_stack();
			break;
		case 3:
			cout << setw(20) << "中序输出: ";
			tree.in_order_traverse();
			break;
		case 4:
			cout << setw(20) << "中序非递归输出: ";
			tree.in_order_traverse_stack();
			break;
		case 5:
			cout << setw(20) << "后序输出: ";
			tree.post_order_traverse();
			break;
		case 6:
			cout << setw(20) << "后序非递归输出: ";
			tree.post_order_traverse_stack();
			break;
		case 7:
			cout << setw(20) << "层遍历非递归输出: ";
			tree.level_order_traverse_queue();
			break;
		case 8:
			cout << setw(20) << "二叉树的深度为：" << tree.length();
			break;
		default: cout << "输入错误："; break;
		}
	}

	return 0;
}