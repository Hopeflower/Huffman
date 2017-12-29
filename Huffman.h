#include<iostream>
#include<list>
#include<stack>
#include<queue>
#include<cstring>
#include<string>
#include<fstream>
#include"HufTree.h"
using namespace std;
template<class T>
class Huffman
{
private:
	struct Node
	{
		T data;
		int weight;
		int parent, left, right;
	};
	Node * elem;
	int length;
public:
	struct Hfcode
	{
		T data;
		string code;
	};
	int Size()const { return(length); }
	Huffman(const T * x, const int* w, int size);
	void GetCode(Hfcode result[]);
	void Trancode(char a[]);
	void EnCode(const Hfcode result[],const T *x,int size);
	void PrintHfTree(int *w,int screenwidth);
	int FindNode(const T& v);
	int FindId(const int &w);
	int FindIdBack(const int &w);
	bool FindID(const int &w);
		~Huffman()
	{
		delete[] elem;
	}

};

template<class T>
inline Huffman<T>::Huffman(const T * x, const int* w, int size)
{
	const int MAX_INT = 1000;
	int min1, min2;
	int z, y;

	length = 2 * size;
	elem = new Node[length];

	for (int i = size; i < length; ++i)
	{
		elem[i].weight = w[i - size];
		elem[i].data = x[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}

	for(int i = size - 1; i >0;--i )
	{
		min1 = min2 = MAX_INT;
		y = z = 0;
		for (int j = i + 1; j < length; ++j)
		{
			if (elem[j].parent == 0)
			{
				if (elem[j].weight < min1)
				{
					min2 = min1;
					min1 = elem[j].weight;
					z = y;
					y = j;
				}
				else if (elem[j].weight < min2)
				{
					min2 = elem[j].weight;
					z = j;
				}
			}
		}
		elem[i].weight = min1 + min2;
		elem[i].left = z;
		elem[i].right = y;
		elem[i].parent = 0;
		elem[z].parent = i;
		elem[y].parent = i;
	}
}

template<class T>
inline void Huffman<T>::GetCode(Hfcode result[])
{
	int size = length / 2;
	int p, s;
	for (int i = size; i < length; ++i)
	{
		result[i - size].data = elem[i].data;
		result[i - size].code = "";
		p = elem[i].parent;
		s = i;
		while (p)
		{
			if (elem[p].left == s)
			{
				result[i - size].code = '0' + result[i - size].code;
			}
			else
			{
				result[i - size].code = '1' + result[i - size].code;
			}
			s = p;
			p = elem[p].parent;
		}
	}
}

template<class T>
inline void Huffman<T>::Trancode(char a[])
{
	int size = length / 2;
	int p = 1;
	for (int i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == '0')
		{
			p = elem[p].left;
			if (elem[p].left == 0 && elem[p].right == 0)
			{
				cout << elem[p].data;
				p = 1;
			}
			
		}
		if (a[i] == '1')
		{
			p = elem[p].right;
			if (elem[p].left == 0 && elem[p].right == 0)
			{
				cout << elem[p].data;
				p = 1;
			}
			
		}

	}
}

template<class T>
inline void Huffman<T>::EnCode(const Hfcode reuslt[],const T * x,int size)
{
	int y;
	int z = length / 2;
	for (int i = 0; i < size; i++)
	{
		y = FindNode(x[i]);
		if (y == -1)
		{
			cout << "This elem is not coded" << endl;
		}
		else
		{
			cout << reuslt[y-z].code;
		}
		
	}
	
}

template<class T>
inline int Huffman<T>::FindNode(const T & v)
{
	int size = length / 2;
	for (int i = size; i < length; i++)
	{
		if (elem[i].data == v)
			return(i);
	}
	return (-1);
}

template<class T>
inline int Huffman<T>::FindId(const int & w)
{
	int size = length / 2;
	for (int i = size; i < length; ++i)
	{
		if (elem[i].weight == w)
		{
			return(i);	
		}
	}
	return (-1);
}

template<class T>
inline int Huffman<T>::FindIdBack(const int & w)
{
	int size = length / 2;
	for (int i = size; i < length; ++i)
	{
		if (elem[i].weight == w)
		{
			for (int j = i + 1; j < length; ++j)
			{
				if (elem[j].weight == w)
				{
					i = j;
				}
			}
			return(i);
		}
	}
	return (-1);
}

template<class T>
inline bool Huffman<T>::FindID(const int & w)
{
	int size = length / 2;
	for (int i = size; i < length; ++i)
	{
		if (elem[i].weight == w)
			return(1);
	}
	return (0);
}


template<class T>
inline void Huffman<T>::PrintHfTree(int * w,int screenwidth)
{
	int x;
	int i = 0;
	int size = length / 2;
	int y[100];
	BTNode<int> *t;
	t = MakeHufm(w, size);
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;
	Location  fLoc, cLoc;
	queue<BTNode<int>*>q;
	queue<Location>LQ;
	fLoc.xindent = offset;
	fLoc.ylevel = level;
	q.push(t);
	LQ.push(fLoc);
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		fLoc = LQ.front();
		LQ.pop();
		Gotxy(fLoc.xindent, fLoc.ylevel);
		if (FindID(t->data)&&(t->left == NULL || t->right == NULL))
		{
				x = FindIdBack(t->data);
				y[i] = x;
				for (int j = 0; j < i; j++)
				{
					if (y[j] == x)
					{
						x = FindId(t->data);
					}

				}
				cout << elem[x].data;
				++i;
			
		}
		else
		{
			cout << t->data;
		}
		if (fLoc.ylevel != level)
		{
			level++; offset = offset / 2;
		}
		if (t->left)
		{
			q.push(t->left);
			cLoc.ylevel = fLoc.ylevel + 1;
			cLoc.xindent = fLoc.xindent - offset / 2;
			LQ.push(cLoc);
		}
		if (t->right)
		{
			q.push(t->right);
			cLoc.ylevel = fLoc.ylevel + 1;
			cLoc.xindent = fLoc.xindent + offset / 2;
			LQ.push(cLoc);
		}
	}
	cout << endl;
}
