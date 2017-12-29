#include<iostream>
#include<vector>
using namespace std;
template<class T>
class Heap
{
private:
	vector<T> vec;                                    //�������������������
	int size;                                        //��ʾ����Ԫ�ظ���
	void BuildHeap(void);                             //�����������������ݵ���Ϊ��
	void PercolateDown(int h);                        //���µ���Ϊ�ѣ���Ҫ����ɾ������
	void PercolateUp();                              //���ϵ���Ϊ�ѣ���Ҫ���ڲ������
	void BuildHeap(T *pa, int size);                  //������H����Ϊ��
	void PercolateDown(T *pa, int pos, int size);     //���±�[POS��size]��Χ�ڵ��������µ���Ϊ��
public:
	explicit Heap(int max = 100) :vec(max), size(0) {}  //�����ն�
	explicit Heap(const vector<T> & vt);               //����������󴴽�����
	bool Empty(void)const { return (size == 0); }        //�ж϶��Ƿ�Ϊ��
	int Size(void) { return(size); }                   //ȡ�ѵ�����Ԫ�صĸ���

	void Insert(const T & item);                      //�Ѳ���
	const T &Top(void)const { return (vec[0]); }       //ȡ����Ԫ��
	void DeleteMin(void);                            //ɾ������Ԫ��
	void DeleteMin(T&item);                          //��ɾ����Ԫ����Ϊ��������
	void Clear(void) { size = 0; }                   //�����
	void HeapSort(T *pa, int n);
};


//�����������������ݵ���Ϊ��
template<class T>
inline void Heap<T>::BuildHeap(void)
{
	for (int i = size / 2 - 1; i >= 0; i--)       //�����һ����Ҷ�ӽ�������ڵ�
		PercolateDown(i);                       //���Է�Ҷ�ӽ��Ϊ����Ϊ��������Ϊ��
}


//���µ���Ϊ�ѣ���Ҫ����ɾ������
template<class T>
inline void Heap<T>::PercolateDown(int h)
{
	int p = h, c = 2 * p + 1;                   //p��c�ֱ��ʾ˫�׺ͺ�������
	T temp = vec[p];
	while (c < size)
	{
		if (c + 1 < size&&vec[c + 1] < vec[c])   //ȥ���Һ����е���С��
			++c;
		if (temp <= vec[c])                      //С�����Һ���
			break;
		else                                    // �������Һ���
		{
			vec[p] = vec[c];                    //�����Һ��Ӻ�����С���Ƶ���˫��λ��
			p = c;                             //�ǰ���ӽ��Ϊ˫�׽��
			c = 2 * p + 1;                     //ȡ�������±�
		}
	}
	vec[p] = temp;                             //ȡ���ݴ�ĸ��Ƶ��������λ��
}


//���ϵ���Ϊ�ѣ���Ҫ���ڲ������
template<class T>
inline void Heap<T>::PercolateUp()
{
	int c = size - 1, p = (c - 1) / 2;       //p��c�ֱ��ʾ˫�׺ͺ�������
	T temp = vec[c];                        //��β����ݴ�
	while (c > 0)
	{
		if (vec[p] <= temp)                //��С��˫�׽��
			break;
		else
		{
			vec[c] = vec[p];                //��˫���Ƶ�����λ��
			c = p;                         //�ǰ���ӽ��Ϊ˫�׽��
			p = (c - 1) / 2;
		}
	}

		vec[c] = temp;
	                         //���ݴ��Ԫ���Ƶ��������λ��
}

template<class T>
inline void Heap<T>::BuildHeap(T * pa, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		PercolateDown(pa, i, size);
}

template<class T>
inline void Heap<T>::PercolateDown(T * pa, int pos, int size)
{
	int p = pos, c = 2 * p + 1;
	T temp = pa[p];
	while (c < size)
	{
		if (c + 1 < size&&pa[c + 1] > pa[c])
			++c;
		if (temp >= pa[c])
			break;
		else
		{
			pa[p] = pa[c];
			p = c;
			c = 2 * p + 1;
		}
	}
}


//����������󴴽�����
template<class T>
inline Heap<T>::Heap(const vector<T>& vt) :vec(vt.size() + 10), size(vt.size())
{
	for (int i = 0; i < size; i++)          //����������vt���Ƹ��Ѷ�������������vec
		vec[i] = vt[i];
	BuildHeap();                           //��������������Ϊ��
}


//�Ѳ���
template<class T>
inline void Heap<T>::Insert(const T & item)
{
	if (size == vec.size())       //����ռ�����
		vec.resize(vec.size() * 2);   //������������
	vec[size] = item;               // β��
	size++;                        //Ԫ�ظ�������1
	PercolateUp();                   //�ѵ���
}


//ɾ������Ԫ��
template<class T>
inline void Heap<T>::DeleteMin(void)
{
	if (size == 0)
	{
		cout << "Heap empty!";
		exit(1);
	}
	vec[0] = vec[size - 1];         //βԪ���Ƶ���λλ��
	size--;                         //Ԫ�ظ�����1
	PercolateDown(0);                   //���µ���Ϊ��
}


//��ɾ����Ԫ����Ϊ��������
template<class T>
inline void Heap<T>::DeleteMin(T & item)
{
	if (size == 0)
	{
		cout << "Heap empty!";
		exit(1);
	}
	item = vec[0];
	vec[0] = vec[size - 1];
	size--;
	PercolateDown(0);
}

template<class T>
inline void Heap<T>::HeapSort(T * pa, int n)
{
	T temp;
	BuildHeap(pa, n);
	for (int i = n - 1; i > 0; i--)
	{
		temp = pa[0];
		pa[0] = pa[i];
		pa[i] = temp;
		PercolateDown(pa, 0, i);
	}
}
