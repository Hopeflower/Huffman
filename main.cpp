#include<iostream>
#include"Huffman.h"
using namespace std;

void menu()
{
	    cout << endl;
	    cout << "       ┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓" << endl;
	    cout << "       ┃      ★★★★★★★哈夫曼编码与译码★★★★★★★        ┃" << endl;
	    cout << "       ┃                   1.  创建哈夫曼树并显示哈夫曼树         ┃" << endl;
	    cout << "       ┃                   2.  进行哈夫曼编码                     ┃" << endl;
		cout << "       ┃                   3.  进行哈夫曼文本加密                 ┃" << endl;
	    cout << "       ┃                   4.  进行哈夫曼文本译码                 ┃" << endl;
	    cout << "       ┃                   5.  退出程序                           ┃" << endl;
	    cout << "       ┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛" << endl;
	    cout << "                       <><注意：空格字符用'- '代替><>" << endl;
	    cout << endl;
}

void main()
{
	const int MAX_SIZE = 100;
	char ch[MAX_SIZE];
	int w[MAX_SIZE];
	int flag;
	menu();
	while (1)
	{
		int num;
		cout << "<><请选择功能(1-创建 2-编码 3-加密 4-译码  5-退出)><>: ";
		cin >> num;
		switch (num)
		{
		case 1:
		{
			cout << "输入字符的个数:\t";
			cin >> flag;
			cout << endl;
			cout << "输入字符：\0";
			for (int i = 0; i < flag; i++)
			{
				cin >> ch[i];
			}
			cout << "输入权值：\0";
			for (int i = 0; i < flag; i++)
			{
				cin >> w[i];
			}
			Huffman<char> tree(ch, w, flag);
			tree.PrintHfTree(w, 100);
			cout << endl;
			break;
		}
		case 2:
		{
			Huffman<char> tree(ch, w, flag);
			Huffman<char>::Hfcode reuslt[50];
			tree.GetCode(reuslt);
			cout << "字符" << '\t' << "编码" << endl;
			for (int i = 0; i < flag; i++)
			{
				cout << reuslt[i].data << "\t" << reuslt[i].code << endl;
			}
			cout << endl;
			break;
		}
		case 3:
		{
			int x=0;
			char T[MAX_SIZE];
			Huffman<char> tree(ch, w, flag);
			Huffman<char>::Hfcode reuslt[27];
			tree.GetCode(reuslt);
			cout << "输入文本,当输入为‘#’时停止: ";
			while (T[x - 1] != '#')
			{
				cin >> T[x];
				x++;
			}
			tree.EnCode(reuslt, T, x-1);

				cout << endl;
			break;
		}
		case 4:
		{
			int x=0;
			char T[MAX_SIZE];
			Huffman<char> tree(ch, w, flag);
			Huffman<char>::Hfcode reuslt[27];
			tree.GetCode(reuslt);
			cout << "输入文本，当输入'#'时停止: ";
			while (T[x-1]!='#')
			{
				cin >> T[x];
				x++;
			}
			tree.Trancode(T);
			cout << endl;
			break;
		}
		case 5:
			cout << endl;
			cout << "<><退出成功！><>" << endl;
			exit(0);
		default:
			break;		         
		
		}



	}
}
