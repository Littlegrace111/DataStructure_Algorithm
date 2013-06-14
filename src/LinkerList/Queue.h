#ifndef _QUEUE_H
#define _QUEUE_H

#include "SLinker.h"

template<typename T>
class CQueue: public CSLinker<T>{
public:
	void EnQueue(const T data)//在队尾加入元素
	{
		AddTail(data);
	}
	
	T   DeQueue()//在队头删除元素
	{
		T data = GetAt(0);
		DeleteAt(0);
		return data;
	}

	T&  GetFront()
	{
		return GetAt(0);
	}

	T   GetFront() const
	{
		return GetAt(0);
	}

	T&  GetRear()
	{
		return GetAt(GetCount());
	}

	T   GetRear() const
	{
		return GetAt(GetCount());
	}
};

#endif