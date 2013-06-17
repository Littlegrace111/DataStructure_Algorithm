#ifndef _HEAP_H
#define _HEAP_H

template <class T>
class MinHeap{
private:
	T* heapArray; // 存放堆数据的数组
	int CurrentSize; // 当前堆中元素数目
	int MaxSize; //堆所能容纳的最大元素数目
	void BuildHeap(); //建堆
public:
	MinHeap(const int n); //构造函数， n表示初始化堆的最大元素数目
	virtual ~MinHeap(){ delete []heapArray; }

	bool isLeaf(int pos) const; //叶子结点，返回ture
	int leftChild(int pos) const; //返回左孩子的位置
	int rightChild(int pos) const; //返回右孩子的位置
	int parent(int pos) const; //返回父结点的位置
	bool Remove(int pos, T& node); // 删除给定下标的元素
	bool Insert(const T& newnode); //向堆中插入新元素
	T& RemoveMin();// 从堆顶删除最小元素
	void SiftUp(int position); //从position向上开始调整，使序列成为堆
	void SiftDown(int position); // 筛选法函数，参数left表示开始处理的数组下标
};

//建堆
//从堆的第一个分支结点heapArray[CurrentSize/2-1]
//开始，自低向上逐步把一各个分支结点为根的子树调整成堆
template <class T>
inline void MinHeap<T>::BuildHeap()
{
	//反复调用筛选函数
	
}

//筛选法
template <class T>
inline void MinHeap<T>::SiftDown( int position )
{
	int i = position; // 标识父结点
	int j = 2*i+1; // 标识关键值较小的子结点
	T temp = heapArray[i]; //保存父结点
	//过筛
	while(j<CurrentSize){
		if((j<CurrentSize-1)&&(heapArray[j]>heapArray[j+1]))
			j++; //j指向数值较小的子结点
		if(temp>heapArray[j]){
			heapArray[i] = heapArray[j];
			i = j;
			j = 2*j+1;//向下继续
		}// end if
		else 
			break;
	}
	heapArray[i] = temp;
}

template <class T>
inline int MinHeap<T>::parent( int pos ) const
{
	return (pos-1)/2; //返回父结点位置
}

template <class T>
inline int MinHeap<T>::rightChild( int pos ) const
{
	return 2*pos+2; // 返回右孩子的位置
}

template <class T>
inline int MinHeap<T>::leftChild( int pos ) const
{
	return 2*pos+1;//返回左孩子的位置
}

template <class T>
inline bool MinHeap<T>::isLeaf( int pos ) const
{
	return (pos>=CurrentSize/2)&&(pos<CurrentSize);
}

template <class T>
inline MinHeap<T>::MinHeap( const int n )
{
	if(n<=0) return;
	CurrentSize = 0;
	MaxSize = n; //初始化堆的容量为n
	heapArray = new T[MaxSize]; // 创建堆空间
	BuildHeap(); //此处进行堆元素的赋值工作
}

#endif