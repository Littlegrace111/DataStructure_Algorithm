#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>

template <class T>
class MinHeap{
public:
	MinHeap(const int n); //���캯���� n��ʾ��ʼ���ѵ����Ԫ����Ŀ
	virtual ~MinHeap(){ delete []heapArray; }

private:
	T* heapArray; // ��Ŷ����ݵ�����
	int CurrentSize; // ��ǰ����Ԫ����Ŀ
	int MaxSize; //���������ɵ����Ԫ����Ŀ

	//void BuildHeap(); //����
	//void SiftUp(int position); //��position���Ͽ�ʼ������ʹ���г�Ϊ��
	//void SiftDown(int position); // ɸѡ������������left��ʾ��ʼ����������±�
	void swap(T& lvalue, T& rvalue);

public:
	bool isLeaf(int pos) const; //Ҷ�ӽ�㣬����ture
	int leftChild(int pos) const; //�������ӵ�λ��
	int rightChild(int pos) const; //�����Һ��ӵ�λ��
	int parent(int pos) const; //���ظ�����λ��

	bool Insert(const T& newnode); //Ԫ�����
	bool Remove(T& node); // Ԫ�س���

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
	if(CurrentSize == MaxSize)//����
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
	MaxSize = n; //��ʼ���ѵ�����Ϊn
	heapArray = new T[MaxSize]; // �����ѿռ�
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