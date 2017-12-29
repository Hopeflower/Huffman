#include<iostream>
#include"Huffman.h"
using namespace std;

void menu()
{
	    cout << endl;
	    cout << "       ��������������������������������������������������������������" << endl;
	    cout << "       ��      ������������������������������        ��" << endl;
	    cout << "       ��                   1.  ����������������ʾ��������         ��" << endl;
	    cout << "       ��                   2.  ���й���������                     ��" << endl;
		cout << "       ��                   3.  ���й������ı�����                 ��" << endl;
	    cout << "       ��                   4.  ���й������ı�����                 ��" << endl;
	    cout << "       ��                   5.  �˳�����                           ��" << endl;
	    cout << "       ��������������������������������������������������������������" << endl;
	    cout << "                       <><ע�⣺�ո��ַ���'- '����><>" << endl;
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
		cout << "<><��ѡ����(1-���� 2-���� 3-���� 4-����  5-�˳�)><>: ";
		cin >> num;
		switch (num)
		{
		case 1:
		{
			cout << "�����ַ��ĸ���:\t";
			cin >> flag;
			cout << endl;
			cout << "�����ַ���\0";
			for (int i = 0; i < flag; i++)
			{
				cin >> ch[i];
			}
			cout << "����Ȩֵ��\0";
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
			cout << "�ַ�" << '\t' << "����" << endl;
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
			cout << "�����ı�,������Ϊ��#��ʱֹͣ: ";
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
			cout << "�����ı���������'#'ʱֹͣ: ";
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
			cout << "<><�˳��ɹ���><>" << endl;
			exit(0);
		default:
			break;		         
		
		}



	}
}
