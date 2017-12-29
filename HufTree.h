#include<iostream>
#include<vector>
#include"BTNodeTree.h"
#include"Heap.h"
using namespace std;
//Creat HufmNode
template<class T>
struct HufmNode
{
	BTNode<T> *t;
	int operator<(const HufmNode & h) { return (t->data < h.t->data); }
	int operator<=(const HufmNode & h) { return (t->data <= h.t->data); }
};


//MakeHuffmanTree
template<class T>
BTNode<T> * MakeHufm(const T*pa, int n)
{
	HufmNode<T> hf;
	BTNode<T> *t, *left, *right;
	Heap<HufmNode<T>>H(n);
	for (int i = 0; i < n; i++)
	{
		t = GetBTNode(pa[i]);
		hf.t = t;
		H.Insert(hf);
	}
	for (int i = 1; i < n; i++)
	{
		H.DeleteMin(hf);
		right = hf.t;
		H.DeleteMin(hf);
		left = hf.t;
		if (right->data == left->data&&(left->right!=NULL||left->left!=NULL)) //若权值相同交换左右孩子
		{ 
			t = GetBTNode(left->data + right->data, right, left);
		}
		else
		{
			t = GetBTNode(left->data + right->data, left, right);   //构建二叉树
		}
		hf.t = t;
		H.Insert(hf);
	}
	H.DeleteMin(hf);
	t = hf.t;
	return (t);
}