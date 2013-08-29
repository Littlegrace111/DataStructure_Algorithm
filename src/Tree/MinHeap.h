#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>

template <class T>
class MinHeap{
public:
	MinHeap(const int n); //构造函数， n表示初始化堆的最大元素数目
	virtual ~MinHeap(){ delete []heapArray; }

private:
	T* heapArray; // 存放堆数据的数组
	int CurrentSize; // 当前堆中元素数目
	int MaxSize; //堆所能容纳的最大元素数目

	//void BuildHeap(); //建堆
	//void SiftUp(int position); //从position向上开始调整，使序列成为堆
	//void SiftDown(int position); // 筛选法函数，参数left表示开始处理的数组下标
	void swap(T& lvalue, T& rvalue);

public:
	bool isLeaf(int pos) const; //叶子结点，返回ture
	int leftChild(int pos) const; //返回左孩子的位置
	int rightChild(int pos) const; //返回右孩子的位置
	int parent(int pos) const; //返回父结点的位置

	bool Insert(const T& newnode); //元素入堆
	bool Remove(T& node); // 元素出堆

	void debug_preview();
};

template <class T>
void MinHeap<T>::debug_preview()
{
	for(int i=0; i<CurrentSize; i++)
	{
		std::cout<<heapArray[i]<<" ";
	}
	std::cout<<std::endl;
}

// switch first element to a smaller leaf node
template <class T>
bool MinHeap<T>::Remove( T& node )
{
	if(CurrentSize == 0)
		return false;

	node = heapArray[0];
	int index = 0;
	while(!isLeaf(index)){//if not leaf node
		int leftchild_pos = leftChild(index);
		int rightchild_pos = rightChild(index);
		if(leftchild_pos && rightchild_pos)
		{   //if left child and right child both exist.
			if(heapArray[leftchild_pos] < heapArray[rightchild_pos])
			{
				swap(heapArray[index], heapArray[leftchild_pos]);
				index = leftchild_pos;
			}else{
				swap(heapArray[index], heapArray[rightchild_pos]);
				index = rightchild_pos;
			}
		}else if(leftchild_pos){// right child must be 0
			swap(heapArray[index], heapArray[leftchild_pos]);
			index = leftchild_pos;
			break;
		}else
			break;
	}

	// move the last element to the switch position
	// of course, if it is the blank one, forget it
	if(index < CurrentSize-1)
	{
		heapArray[index] = heapArray[CurrentSize-1];
		while(heapArray[index] < heapArray[parent(index)])
		{
			swap(heapArray[index], heapArray[parent(index)]);
			index = parent(index);
		}
	}

	CurrentSize--;
#ifdef _DEBUG
	debug_preview();
#endif
	return true;
}

template <class T>
void MinHeap<T>::swap( T& lvalue, T& rvalue )
{
	T temp;
	temp = lvalue;
	lvalue = rvalue;
	rvalue = temp;
}

//1. put element to the end of the array
//2. get parent of this element
//3. if element is smaller than its parent, swap them;
template <class T>
bool MinHeap<T>::Insert( const T& newnode )
{
	if(CurrentSize == MaxSize)//堆满
		return false;
	//put element to the end of the array
	heapArray[CurrentSize] = newnode;
	CurrentSize++;

	int index = CurrentSize - 1;

	if(parent(index) >= 0)//if not root node
	{
		while(heapArray[index] < heapArray[parent(index)]){
			swap(heapArray[index], heapArray[parent(index)]);
			index = parent(index);
		}
	}
#ifdef _DEBUG
	debug_preview();
#endif
	return true;
}

template <class T>
inline MinHeap<T>::MinHeap( const int n )
{
	if(n<=0) return;
	CurrentSize = 0;
	MaxSize = n; //初始化堆的容量为n
	heapArray = new T[MaxSize]; // 创建堆空间
}

//return parent position.
template <class T>
inline int MinHeap<T>::parent( int pos ) const
{
	if(pos == 0)// root node do not have parent.
		return -1;
	else
	    return (pos-1)/2;
}

// return position of right child
// if not have right child, return 0.
template <class T>
inline int MinHeap<T>::rightChild( int pos ) const
{
	return ((2*pos+2 < CurrentSize)? (2*pos+2):0);
}

// return posistion of left child
// if not have left child, return 0.
template <class T>
inline int MinHeap<T>::leftChild( int pos ) const
{
	return ((2*pos+1 < CurrentSize)? (2*pos+1):0);
}

template <class T>
inline bool MinHeap<T>::isLeaf( int pos ) const
{
	return (pos>=CurrentSize/2)&&(pos<CurrentSize);
}


#endif