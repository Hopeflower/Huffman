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
	struct Node                          //Huffman结点
	{
		T data;
		int weight;
		int parent, left, right;
	};
	Node * elem;
	int length;
public:
	struct Hfcode                       //Huffman代码结点
	{
		T data;
		string code;
	};
	int Size()const { return(length); }   //Huffman的空间大小

	Huffman(const T * x, const int* w, int size);    //构造Huffman树
	void GetCode(Hfcode result[]);                  //对Huffman进行编码
	void Trancode(char a[]);                       //用Huffman树翻译加密的文本
	void EnCode(const Hfcode result[],const T *x,int size);  //用构建的Huffman树对文本进行加密
	void PrintHfTree(int *w,int screenwidth);        //用二叉树的方式输出Huffman树
	int FindNode(const T& v);                      //找的Huffman树数据的下标
	int FindId(const int &w);                      //找到前面权值的下标
	int FindIdBack(const int &w);                  //找到后面权值的下标    
	bool FindID(const int &w);                    //判断权值是否存在
		~Huffman()                               // Huffman的析构函数
	{
		delete[] elem;
	}

};

//构造哈夫曼树
template<class T>
inline Huffman<T>::Huffman(const T * x, const int* w, int size)             //利用下标创建哈夫曼树
{
	const int MAX_INT = 1000;                                          
	int min1, min2;                                                    //用来表示最小两个叶子的值
	int z, y;

	length = 2 * size;
	elem = new Node[length];                                         //对Huffman地址空间进行初始化

	for (int i = size; i < length; ++i)                             //对哈夫曼树进行初始化
	{
		elem[i].weight = w[i - size];                              //将权值储存在Huffman中
		elem[i].data = x[i - size];                                //将数据存储在Huffman中
		elem[i].parent = elem[i].left = elem[i].right = 0;          //对叶子结点，和父结点进行初始化
	}

	for(int i = size - 1; i >0;--i )
	{
		min1 = min2 = MAX_INT;                                   //对min1和min2进行初始化
		y = z = 0;
		for (int j = i + 1; j < length; ++j)
		{
			if (elem[j].parent == 0)
			{
				if (elem[j].weight < min1)                      //选择最小叶子节点
				{
					min2 = min1;
					min1 = elem[j].weight;
					z = y;
					y = j;
				}
				else if (elem[j].weight < min2)               //选择次小的叶子结点
				{
					min2 = elem[j].weight;
					z = j;
				}
			}
		}
		elem[i].weight = min1 + min2;                      //把权值的和存入权值中
		elem[i].left = z;                                 //把次小的叶子结点下标存入左子树中
		elem[i].right = y;                                //把最小的叶子结点下标存入右子树中
		elem[i].parent = 0;                               
		elem[z].parent = i;                               //构建左子树父结点
		elem[y].parent = i;                               //构建右子树父结点 
	}
}

//对构造Huffman树进行编码
template<class T>
inline void Huffman<T>::GetCode(Hfcode result[])
{
	int size = length / 2;
	int p, s;
	for (int i = size; i < length; ++i)
	{
		result[i - size].data = elem[i].data;                 //把哈夫曼树中的data赋给代码结点的data
		result[i - size].code = "";                          //Huffman编码的初始化
		p = elem[i].parent;
		s = i;
		while (p)                                          //利用叶子结点下标的反向构建编码
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

//用Huffman进行文本解密
template<class T>                          
inline void Huffman<T>::Trancode(char a[])
{
	int size = length / 2;
	int p = 1;
	for (int i = 0; a[i] != '\0'; i++)                //当为'0'遍历左子树
	{
		if (a[i] == '0')
		{
			p = elem[p].left;                       //把左子树下标赋给p
			if (elem[p].left == 0 && elem[p].right == 0) 
			{
				cout << elem[p].data;              //输出找到结点的数值
				p = 1;
			}
			
		}
		if (a[i] == '1')                           //当为‘1’遍历右子树
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

//进行文本加密
template<class T>
inline void Huffman<T>::EnCode(const Hfcode reuslt[],const T * x,int size)
{
	int y;
	int z = length / 2;
	for (int i = 0; i < size; i++)
	{
		y = FindNode(x[i]);                 //找到文本为在z【i】数据的下标
		if (y == -1)
		{
			cout << "This elem is not coded" << endl;
		}
		else
		{
			cout << reuslt[y-z].code;     //输出改数值的编码
		}
		
	}
	
}

//寻找'v'的下标
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

//寻找权值下标
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

//寻找相同权值后面的下标
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

//判断是否存在改权值
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

//以二叉树方式输出Huffman树
template<class T>
inline void Huffman<T>::PrintHfTree(int * w,int screenwidth)
{
	int x;
	int i = 0;
	int size = length / 2;
	int y[100];
	BTNode<int> *t;
	t = MakeHufm(w, size);                     //用Huffman的权值构建二叉树
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;   //从0层开始遍历
	Location  fLoc, cLoc;                    //记录父结点，子结点的输出位置
	queue<BTNode<int>*>q;                    //储存结点指针的队列
	queue<Location>LQ;                       //储存结点输出位置的队列
	fLoc.xindent = offset;             
	fLoc.ylevel = level;
	q.push(t);                              //根入指针队列
	LQ.push(fLoc);                          //根结点位置数据入队列
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		fLoc = LQ.front();
		LQ.pop();
		Gotxy(fLoc.xindent, fLoc.ylevel);   //确定输出光标的位置
		if (FindID(t->data)&&(t->left == NULL || t->right == NULL))  //把权值转化成数据输出
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
		if (fLoc.ylevel != level)                      //层数增加一，缩进减半
		{
			level++; offset = offset / 2;
		}
		if (t->left)                                     //如果有左孩子，对左孩子进行操作
		{
			q.push(t->left);
			cLoc.ylevel = fLoc.ylevel + 1;
			cLoc.xindent = fLoc.xindent - offset / 2;
			LQ.push(cLoc);
		}
		if (t->right)                                   //如果有右孩子，对左孩子进行操作
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
	int xindent, ylevel;              //结点位置结点
};

void Gotxy(int x, int y)             //输出位置
{
	static int level = 0, indent = 0; 
	if (y == 0)                     //输出二叉树重新赋值   
	{
		indent = 0; level = 0;
	}
	if (level != y)              // 若增加层数，缩进量从0开始
	{
		cout << endl;
		indent = 0; level++;
	}
	cout.width(x - indent);     //根据已有缩进量确定当前缩进量
	indent = x;                //记录当前缩进量
}