#include<iostream>
#include<vector>
using namespace std;
template<class T>
class Heap
{
private:
	vector<T> vec;                                    //向量容器，用来储存堆
	int size;                                        //表示数据元素个数
	void BuildHeap(void);                             //把向量容器类中数据调整为堆
	void PercolateDown(int h);                        //向下调整为堆，主要用于删除操作
	void PercolateUp();                              //向上调整为堆，主要用于插入操作
	void BuildHeap(T *pa, int size);                  //将数组H调整为堆
	void PercolateDown(T *pa, int pos, int size);     //将下标[POS，size]范围内的数据向下调整为堆
public:
	explicit Heap(int max = 100) :vec(max), size(0) {}  //建立空堆
	explicit Heap(const vector<T> & vt);               //用向量类对象创建对象
	bool Empty(void)const { return (size == 0); }        //判断堆是否为空
	int Size(void) { return(size); }                   //取堆的数据元素的个数

	void Insert(const T & item);                      //堆插入
	const T &Top(void)const { return (vec[0]); }       //取堆首元素
	void DeleteMin(void);                            //删除堆首元素
	void DeleteMin(T&item);                          //把删除的元素作为参数返回
	void Clear(void) { size = 0; }                   //堆清空
	void HeapSort(T *pa, int n);
};


//把向量容器类中数据调整为堆
template<class T>
inline void Heap<T>::BuildHeap(void)
{
	for (int i = size / 2 - 1; i >= 0; i--)       //从最后一个非叶子结点至根节点
		PercolateDown(i);                       //将以非叶子结点为根的为子树调整为堆
}


//向下调整为堆，主要用于删除操作
template<class T>
inline void Heap<T>::PercolateDown(int h)
{
	int p = h, c = 2 * p + 1;                   //p和c分别表示双亲和孩子作标
	T temp = vec[p];
	while (c < size)
	{
		if (c + 1 < size&&vec[c + 1] < vec[c])   //去左右孩子中的最小者
			++c;
		if (temp <= vec[c])                      //小于左右孩子
			break;
		else                                    // 大于左右孩子
		{
			vec[p] = vec[c];                    //把左右孩子孩子最小者移到其双亲位置
			p = c;                             //令当前孩子结点为双亲结点
			c = 2 * p + 1;                     //取其左孩子下标
		}
	}
	vec[p] = temp;                             //取把暂存的根移到调整后的位置
}


//向上调整为堆，主要用于插入操作
template<class T>
inline void Heap<T>::PercolateUp()
{
	int c = size - 1, p = (c - 1) / 2;       //p和c分别表示双亲和孩子作标
	T temp = vec[c];                        //把尾结点暂存
	while (c > 0)
	{
		if (vec[p] <= temp)                //不小于双亲结点
			break;
		else
		{
			vec[c] = vec[p];                //把双亲移到孩子位置
			c = p;                         //令当前孩子结点为双亲结点
			p = (c - 1) / 2;
		}
	}

		vec[c] = temp;
	                         //把暂存的元素移到调整后的位置
}

 //将数组H调整为堆
template<class T>
inline void Heap<T>::BuildHeap(T * pa, int size)  
{
	for (int i = size / 2 - 1; i >= 0; i--)      //从邻近的叶子的第一个非叶子结点至根结点
		PercolateDown(pa, i, size);              //将下标【i，size】范围内的数据向下调整为堆
}

//将下标为【POS，size】向下调整为堆
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


//用向量类对象创建对象
template<class T>
inline Heap<T>::Heap(const vector<T>& vt) :vec(vt.size() + 10), size(vt.size())
{
	for (int i = 0; i < size; i++)          //把向量对象vt复制给堆对象的向量类对象vec
		vec[i] = vt[i];
	BuildHeap();                           //把向量类对象调整为堆
}


//堆插入
template<class T>
inline void Heap<T>::Insert(const T & item)
{
	if (size == vec.size())       //如果空间已满
		vec.resize(vec.size() * 2);   //扩大数组容量
	vec[size] = item;               // 尾插
	size++;                        //元素个数增加1
	PercolateUp();                   //堆调整
}


//删除堆首元素
template<class T>
inline void Heap<T>::DeleteMin(void)
{
	if (size == 0)
	{
		cout << "Heap empty!";
		exit(1);
	}
	vec[0] = vec[size - 1];         //尾元素移到首位位置
	size--;                         //元素个数减1
	PercolateDown(0);                   //向下调整为堆
}


//把删除的元素作为参数返回
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

//堆排序
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
