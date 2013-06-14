#ifndef _SLINKER_H
#define _SLINKER_H
#include <iostream>
#include <stdexcept>
#include "..\Common\MemoryLeakTest.h"
#include "..\Common\HandleException.h"

template<typename T>
struct CNode{
	T data;//element
	CNode<T>* next;//next point
	CNode():data(T()), next(NULL) {}
	CNode(const T& initdata): data(T(initdata)), next(NULL) { }
};

//此单链表的设计没有哑节点(dummy node)：插入和删除操作都要考虑头节点更新问题
//此单链表的位置设计与数组访问的方式一致，从位置0开始访问，到m_nCount-1的位置
//考虑设计有头节点和尾节点的链表，简化代码操作
template<typename T>
class CSLinker{
protected:
	int m_nCount;
	CNode<T>* m_pNodeHead;//需要考虑实现自己的拷贝构造函数和析构函数
public:
	CSLinker():m_nCount(0), m_pNodeHead(NULL) {}
	~CSLinker() { RemoveAll(); }
private://interfaces
	int InsertNode(const int pos, const T data);
	int RemoveNode(const int pos);
	void RemoveAll();
public:
	bool IsEmpty()const { return((m_nCount==0)?true:false); }
	int GetCount()const { return m_nCount; }
	T& GetAt(const int pos); 
    T  GetAt(const int pos)const;
	void SetAt(const int pos, const T data);
	void AddTail(const T data) { InsertNode(GetCount(), data); }
	void DeleteAt(const int pos) { RemoveNode(pos); }

	void AddHead(const T data) //更新头节点
	{  
		CNode<T>* pNewNode = new CNode<T>;
		pNewNode->data = data;
		pNewNode->next = m_pNodeHead;
		m_pNodeHead = pNewNode;
		++m_nCount;
	}

    void Debug_print();
};

template<typename T>
inline void CSLinker<T>::SetAt(const int pos, const T data)
{
	try{ 
		if(pos < 0)
			throw MyException("position can not be negative number!");
		if(pos >= m_nCount)
			throw MyException("position is out of range!");
		if(IsEmpty())
			throw MyException("list is empty!");

		CNode<T>* pTempNode = m_pNodeHead;
		for(int i=0; i<pos; i++)
		{
			pTempNode = pTempNode->next;
		}
		pTempNode->data = data;
	}
	catch (MyException& e)
	{
		std::cout<<"[ERROR (CSLinker<T>::SetAt)]: "<<e.GetErrorInfo()<<std::endl;
	}
}

template<typename T>
inline T CSLinker<T>::GetAt( const int pos )const
{
	try{
		if(pos<0)
			throw MyException("position can not be negative number!");
		if(pos>m_nCount-1)
			throw MyException("position is out of range!");
		if(IsEmpty())
			throw MyException("list is empty!");

		CNode<T>* pTempNode = m_pNodeHead;
		for(int i=0; i<pos; i++)
		{
			pTempNode = pTempNode->next; 
		}
		return pTempNode->data;
	}
	catch (MyException& e)
	{
		std::cout<<"[ERROR (CSLinker<T>::GetAt)const]: "<<e.GetErrorInfo()<<std::endl;
		return m_pNodeHead->data;
	}
}

template<typename T>
inline T& CSLinker<T>::GetAt( const int pos )
{
	try{
		if(pos<0)
			throw MyException("position can not be negative number!");
		if(pos>m_nCount-1)
			throw MyException("position is out of range!");
		if(IsEmpty())
			throw MyException("list is empty!");

		CNode<T>* pTempNode = m_pNodeHead;
		for(int i=0; i<pos; i++)
		{
			pTempNode = pTempNode->next; 
		}
		return pTempNode->data;
	}
	catch (MyException& e)
	{
		std::cout<<"[ERROR (CSLinker<T>::GetAt)]: "<<e.GetErrorInfo()<<std::endl;
		return m_pNodeHead->data;
	}
}

template<typename T>
inline void CSLinker<T>::RemoveAll()
{
	CNode<T>* pTempNode = NULL;
	for(int i=0; i<m_nCount; i++)
	{
		pTempNode = m_pNodeHead->next;
		delete m_pNodeHead;
		m_pNodeHead = pTempNode;
	}
	m_nCount = 0;
}

template<typename T>
inline void CSLinker<T>::Debug_print()
{
	try{
		if(IsEmpty())
			throw MyException("list is empty");

	    CNode<T>* pTempNode = m_pNodeHead;
	    for(int i=0; i<=m_nCount-1; i++)
	    {
	        std::cout<<pTempNode->data<<" ";
			pTempNode = pTempNode->next; 
        }
	    std::cout<<std::endl;
	}
	catch(MyException& e)
	{
		std::cout<<"[ERROR (CSLinker<T>::Debug_print)]: "<<e.GetErrorInfo()<<std::endl;
	}
}

//不能删除没有元素的空表
//因为没有引入哑节点，所以需要考虑删除头节点，头节点指针更新的问题
//删除成功返回0，删除失败返回非0值
template<typename T>
inline int CSLinker<T>::RemoveNode( int pos )
{
	try{
		if(pos<0 || pos>m_nCount-1)
		    throw MyException("position is illegal!", -1);

		if(IsEmpty())
			throw MyException("list is empty, nothing to remove!", -2);

		CNode<T>* pTempNode = m_pNodeHead;//要删除的节点
		//删除头节点
		if(0 == pos){
			m_pNodeHead = pTempNode->next;
		}else{
			CNode<T>* pPrevious = m_pNodeHead;
			for(int i=0; i<pos; i++)
			{
				pPrevious = pTempNode;
				pTempNode = pTempNode->next;
			}
			pPrevious->next = pTempNode->next;
		}
		--m_nCount;
		delete pTempNode;
		return 0;
	}
	catch(MyException& e){
		std::cout<<"[ERROR (CSLinker<T>::RemoveNode)]: "<<e.GetErrorInfo()<<std::endl;
		return e.GetErrorId();
	}

}

//1. 考虑插入的位置是否合法
//2. 根据data创建新的节点
//3. 检查链表是否为空，若为空，则新节点作为头节点
//4. 若插入失败返回负数，插入成功返回节点的下一个位置
template<typename T>
inline int CSLinker<T>::InsertNode( int pos, T data )
{
	//ASSERT((pos>=1) && (pos<=m_nCount+1));
	try
	{
		//可以插入的位置范围是0到m_nCount
		//当插入位置为0的时候，表示新插入的节点要插入的链表的第一个位置，要更新头节点
		//当插入的位置为m_nCount时，表示新插入的节点要插入到链表尾部
		if(pos<0)
			throw MyException("position can not be negative number!", -1);
		if(pos>m_nCount)
			throw MyException("position is out of range!", -2);

		//创建新节点
		CNode<T>* pNewNode = new CNode<T>;
		pNewNode->data = data;

		if(IsEmpty()){//若链表为空，则表示插入到头节点
			pNewNode->next = m_pNodeHead;
			m_pNodeHead = pNewNode;
		}else{
			CNode<T>* pTempNode = m_pNodeHead;
		    for(int i=0; i<pos-1; i++)
			    pTempNode = pTempNode->next;

		    pNewNode->next = pTempNode->next;
		    pTempNode->next = pNewNode;
		}

		++m_nCount;
		return pos+1;
	}catch(MyException& e){
		std::cout<<"[ERROR (CSLinker<T>::InsertNode)]: "<<e.GetErrorInfo()<<std::endl;
		return e.GetErrorId();
    }
}

#endif