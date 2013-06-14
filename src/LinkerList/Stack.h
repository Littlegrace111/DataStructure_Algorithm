#ifndef _STACK_H
#define _STACK_H
#include <iostream>
#include "SLinker.h"
#include "..\Common\HandleException.h"

template<typename T>
class CStack: public CSLinker<T>{
public:
	void push(T data) { AddTail(data); }//��ջ������û���������˵��
	int pop(T& data );
	int top(T& data) const;
};

//����λ��
template<typename T>
inline int CStack<T>::top( T& data ) const
{
	try{
		if(IsEmpty())
			throw MyException("stack under flow, stack is empty!", -1);
		data = GetAt(GetCount()-1);
		return GetCount()-1;
	}
	catch (MyException& e)
	{
		std::cout<<e.GetErrorInfo()<<std::endl;
		return e.GetErrorId();
	}
	
}

template<typename T>
inline int CStack<T>::pop( T& data /*= NULL*/ )
{
	try{
		if(IsEmpty())
			throw MyException("stack under flow, stack is empty!", -1);
		top(data);
		DeleteAt(GetCount()-1);
		return 0;
	}
	catch (MyException& e)
	{
		std::cout<<e.GetErrorInfo()<<std::endl;
		return e.GetErrorId();
	}
}

#endif