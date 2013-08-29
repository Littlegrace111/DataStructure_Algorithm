#ifndef _MINHEAP_H


template<class T>
class MaxHeap{
 
private:
	T* heapArray;    // 存放堆数据的数组
	int CurrentSize; // 当前堆中元素数目
	int MaxSize;     // 堆所能容纳的最大元素数目
	void BuildHeap(); // 建堆
public:
	//构造函数，初始化堆的最大元素数目
	MaxHeap(const int MaxSize);
	//析构函数
	virtual ~MaxHeap(){ delete []heapArray;};
	//如果是叶结点，返回TRUE
	bool isLeaf(int pos)const;
	//返回左孩子位置
	int leftchild(int pos)const;
	//返回右孩子位置
	int rightchild(int pos)const;
	//返回父结点位置
	int parent(int pos)const;
	//删除给定下标的元素
	bool Remove(int pos, T& node);
	//向堆中插入新元素newnode
	bool Insert(const T& newNode);
	//从堆顶删除最小值
	T& RemoveMax();

};
#endif