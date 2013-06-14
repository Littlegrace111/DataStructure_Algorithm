#ifndef _CIRCLE_LINK_H
#define _CIRCLE_LINK_H

#include "SLinker.h"
#include "..\Common\HandleException.h"

template<typename T>
class CLinker : public CSLinker<T>{
protected:
	CNode<T>* m_pNodeCurr;
public:
	CLinker():m_pNodeCurr(NULL) {}
public:
	T& GetNext();
	void RemoveAt(const int pos);
	int GetCurrentIndex()const;
};

//删除一个节点
//如果删除的是头节点，更新头节点
template<typename T>
inline void CLinker<T>::RemoveAt( const int pos )
{
	ASSERT(pos>=0 && pos<m_nCount);

	CNode<T>* pTempNode = m_pNodeHead;
	if(0 == pos)//若删除头节点
	{
		m_pNodeHead = pTempNode->next;
		m_pNodeCurr = NULL;//更新当前节点
	}else{
		CNode<T>* pPrevious = NULL;//保存其前驱节点
		for(int i=0; i<pos; i++)
		{
			pPrevious = pTempNode;
			pTempNode = pTempNode->next;
		}
		pPrevious->next = pTempNode->next;
		//added for loop list
		m_pNodeCurr = pPrevious;//更新当前节点
	}

	delete pTempNode;
	--m_nCount;
}


//获得当前节点的位置
template<typename T>
inline int CLinker<T>::GetCurrentIndex() const
{
	ASSERT(0 != m_nCount);

	CNode<T>* pTempNode = m_pNodeHead;

	for(int i=0; i<=m_nCount-1; i++)
	{
		if(pTempNode == m_pNodeCurr)
			return i;
		else
			pTempNode = pTempNode->next;
	}

	return -1;//获得失败
}

//把单链表变成循环链表
//循环链表是概念上的，实际上链表的最后一个节点并为指向其头节点;
//循环链表的概念是靠函数来实施的。
//如果当前节点为NULL或者当前节点的最后一个节点，则将其调整为指向头节点，
//否则将其向后移动一个节点，然后返回当前节点的数据
template<typename T>
inline T& CLinker<T>::GetNext()
{
	ASSERT(0 != m_nCount);
	//若当前节点为NULL，或者为最后一个节点
	//当前节点为NULL表示删除了头节点
	if((NULL == m_pNodeCurr) || (NULL == m_pNodeCurr->next))
		m_pNodeCurr = m_pNodeHead;
	else
		m_pNodeCurr = m_pNodeCurr->next;

	return m_pNodeCurr->data;
}

#endif