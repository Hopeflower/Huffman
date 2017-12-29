#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

template<class T>
struct BTNode //Binary Tree Node
{
	T data;
	BTNode * left, *right;  //只向结点走有孩子的指针
	BTNode(const T &item = T(), BTNode * lptr = NULL, BTNode * rptr = NULL) :
		data(item), left(lptr), right(rptr) {}
};

template<class T>
BTNode<T>*GetBTNode(const T&item, BTNode<T> *lp = NULL, BTNode<T>*rp = NULL)
{
	BTNode<T>*p;
	p = new BTNode<T>(item, lp, rp);
	if (p == NULL)
	{
		cout << "Memory allocation failure！" << endl;
	}
	return (p);
}

template  <class T>
BTNode<T> * MakeLinked(const T *pL, const T* iL, int size)  //把顺序存储转化为链式存储
{
	if (size <= 0)
		return(NULL);
	BTNode<T> *t, *left, *right;
	const T *rL;
	int k;
	for (rL = iL; rL < iL + size; rL++)
	{
		if (*rL == *pL)
			break;
	}
	k = rL - iL;
	left = MakeLinked(pL + 1, iL, k);
	right = MakeLinked(pL + k + 1, iL + k + 1, size - k - 1);
	t = GetBTNode(*pL, left, right);
	return(t);
}

template<class T>
void Preoder(const BTNode<T>*t)  // Preoder traversar  recursive algorithm
{
	if (t == NULL)
		return;
	cout << t->data;                        //Access root
	Preoder(t->left);
	Preoder(t->right);

}

template<class T>
void Inoder(const BTNode<T>*t)  // Inoder traversar  recursive algorithm
{
	if (!t)
		return;
	Inoder(t->left);
	cout << t->data;
	Inoder(t->right);

}

template<class T>
void Postoder(const BTNode<T>*t)  // Postoder traversar  recursive algorithm
{
	if (!t)
		return;
	Postoder(t->left);
	Postoder(t->right);
	cout << t->data;
}


template <class T>
void PrintBTree(const BTNode<T>*t, int screenwidth)
{
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;
	Location  fLoc, cLoc;
	queue<const BTNode<T>*>q;
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
		cout << t->data;
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



struct Location
{
	int xindent, ylevel;
};

void Gotxy(int x, int y)
{
	static int level = 0, indent = 0;
	if (y == 0)
	{
		indent = 0; level = 0;
	}
	if (level != y)
	{
		cout << endl;
		indent = 0; level++;
	}
	cout.width(x - indent);
	indent = x;
}