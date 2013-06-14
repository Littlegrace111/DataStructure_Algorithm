#ifndef _QUEUE_H
#define _QUEUE_H

#include "SLinker.h"

template<typename T>
class CQueue: public CSLinker<T>{
public:
	void EnQueue(const T data)//�ڶ�β����Ԫ��
	{
		AddTail(data);
	}
	
	T   DeQueue()//�ڶ�ͷɾ��Ԫ��
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