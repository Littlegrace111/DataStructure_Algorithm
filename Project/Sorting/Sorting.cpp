// Sorting.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>

using namespace std;

#define MYTRACE(fmt, ...) printf("%s/n", fmt);
#define SWAP(a, b) a^=b; b^=a; a^=b

template<typename T>
class CBHeap{
public:
	CBHeap(int size = 100);
	~CBHeap();

	int Enqueue(T value);
	int Dequeue(T &value);
	T GetMin() const;

#ifdef _DEBUG
	void PrintQueue();
#endif
protected:
	T* m_pData;
	int m_MaxSize; //数组最大值
	int m_CurrentSize;//当前数组最大值
};

#ifdef _DEBUG
template<typename T>
inline void CBHeap<T>::PrintQueue()
{
	for(int i=0; i<m_CurrentSize; i++)
		cout<<m_pData[i];
	cout<<endl;
}
#endif

//
template<typename T>
inline T CBHeap<T>::GetMin() const
{
	return m_pData[0];
}

//最小值出堆
template<typename T>
inline int CBHeap<T>::Dequeue( T &value )
{
	if(m_CurrentSize == 0){
		MYTRACE("heap is empty!");
		return -1;
	}
	value = m_pData[0];
	int index = 0;
	while(2*index < m_CurrentSize){
		int left = (2*index+1 < m_CurrentSize)? (2*index+1):0;
		int right = (2*index+2 < m_CurrentSize)? (2*index+2):0;
		if(left && right){ //if both left and right exist!
			if(m_pData[left] < m_pData[right]){
				SWAP(m_pData[index], m_pData[left]);
				index = left;
			}else{
				SWAP(m_pData[index], m_pData[right]);
				index = right;
			}
		}else if(left){
			SWAP(m_pData[index], m_pData[left]);
			index = left;
			break;
		}else
			break;
	}

	//move the last element to the blank position
	if(index = m_CurrentSize-1){
		m_pData[index] = m_pData[m_CurrentSize-1];
		//try to move this element to the top as high as possible
		while(m_pData[index] < m_pData[(index-1)/2]){
			//swap the two value
			SWAP(m_pData[index], m_pData[(index-1)/2]);
			index = (index-1)/2;
		}
	}
	--m_CurrentSize;
	return index;
}

//success: return position of enter queue element
//fail: return negtive value;
template<typename T>
inline int CBHeap<T>::Enqueue( T value )
{
	if(m_CurrentSize == m_MaxSize){
		MYTRACE("heap is full!");
		return -1;
	}
	//Put this value to the end of the array
	m_pData[m_CurrentSize] = value;
	++m_CurrentSize;

	int index = m_CurrentSize-1;
	while(m_pData[index] < m_pData[(index-1)/2]){
		//Swap the two value
		SWAP(m_pData[index], m_pData[(index-1)/2]);
		index = (index-1)/2;
	}
	return index;
}

template<typename T>
inline CBHeap<T>::~CBHeap()
{
	delete[] m_pData;
}

template<typename T>
inline CBHeap<T>::CBHeap( int size /*= 100*/ )
{
	m_pData = new T[size];
	m_MaxSize = size;
	m_CurrentSize = 0;
}



int _tmain(int argc, _TCHAR* argv[])
{
	CBHeap<int> iHeap;
	iHeap.Enqueue(4);
	iHeap.Enqueue(1);
	iHeap.Enqueue(3);
	iHeap.Enqueue(2);
	iHeap.Enqueue(6);
	iHeap.Enqueue(5);
#ifdef _DEBUG
	iHeap.PrintQueue();
#endif

	int value;
	iHeap.Dequeue(value);
	iHeap.Dequeue(value);

#ifdef _DEBUG
	iHeap.PrintQueue();
#endif
	system("pause");
	return 0;
}

