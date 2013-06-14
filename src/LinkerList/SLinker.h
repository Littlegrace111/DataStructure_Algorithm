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

//�˵���������û���ƽڵ�(dummy node)�������ɾ��������Ҫ����ͷ�ڵ��������
//�˵������λ�������������ʵķ�ʽһ�£���λ��0��ʼ���ʣ���m_nCount-1��λ��
//���������ͷ�ڵ��β�ڵ�������򻯴������
template<typename T>
class CSLinker{
protected:
	int m_nCount;
	CNode<T>* m_pNodeHead;//��Ҫ����ʵ���Լ��Ŀ������캯������������
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

	void AddHead(const T data) //����ͷ�ڵ�
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

//����ɾ��û��Ԫ�صĿձ�
//��Ϊû�������ƽڵ㣬������Ҫ����ɾ��ͷ�ڵ㣬ͷ�ڵ�ָ����µ�����
//ɾ���ɹ�����0��ɾ��ʧ�ܷ��ط�0ֵ
template<typename T>
inline int CSLinker<T>::RemoveNode( int pos )
{
	try{
		if(pos<0 || pos>m_nCount-1)
		    throw MyException("position is illegal!", -1);

		if(IsEmpty())
			throw MyException("list is empty, nothing to remove!", -2);

		CNode<T>* pTempNode = m_pNodeHead;//Ҫɾ���Ľڵ�
		//ɾ��ͷ�ڵ�
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

//1. ���ǲ����λ���Ƿ�Ϸ�
//2. ����data�����µĽڵ�
//3. ��������Ƿ�Ϊ�գ���Ϊ�գ����½ڵ���Ϊͷ�ڵ�
//4. ������ʧ�ܷ��ظ���������ɹ����ؽڵ����һ��λ��
template<typename T>
inline int CSLinker<T>::InsertNode( int pos, T data )
{
	//ASSERT((pos>=1) && (pos<=m_nCount+1));
	try
	{
		//���Բ����λ�÷�Χ��0��m_nCount
		//������λ��Ϊ0��ʱ�򣬱�ʾ�²���Ľڵ�Ҫ���������ĵ�һ��λ�ã�Ҫ����ͷ�ڵ�
		//�������λ��Ϊm_nCountʱ����ʾ�²���Ľڵ�Ҫ���뵽����β��
		if(pos<0)
			throw MyException("position can not be negative number!", -1);
		if(pos>m_nCount)
			throw MyException("position is out of range!", -2);

		//�����½ڵ�
		CNode<T>* pNewNode = new CNode<T>;
		pNewNode->data = data;

		if(IsEmpty()){//������Ϊ�գ����ʾ���뵽ͷ�ڵ�
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