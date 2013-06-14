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

//ɾ��һ���ڵ�
//���ɾ������ͷ�ڵ㣬����ͷ�ڵ�
template<typename T>
inline void CLinker<T>::RemoveAt( const int pos )
{
	ASSERT(pos>=0 && pos<m_nCount);

	CNode<T>* pTempNode = m_pNodeHead;
	if(0 == pos)//��ɾ��ͷ�ڵ�
	{
		m_pNodeHead = pTempNode->next;
		m_pNodeCurr = NULL;//���µ�ǰ�ڵ�
	}else{
		CNode<T>* pPrevious = NULL;//������ǰ���ڵ�
		for(int i=0; i<pos; i++)
		{
			pPrevious = pTempNode;
			pTempNode = pTempNode->next;
		}
		pPrevious->next = pTempNode->next;
		//added for loop list
		m_pNodeCurr = pPrevious;//���µ�ǰ�ڵ�
	}

	delete pTempNode;
	--m_nCount;
}


//��õ�ǰ�ڵ��λ��
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

	return -1;//���ʧ��
}

//�ѵ�������ѭ������
//ѭ�������Ǹ����ϵģ�ʵ������������һ���ڵ㲢Ϊָ����ͷ�ڵ�;
//ѭ������ĸ����ǿ�������ʵʩ�ġ�
//�����ǰ�ڵ�ΪNULL���ߵ�ǰ�ڵ�����һ���ڵ㣬�������Ϊָ��ͷ�ڵ㣬
//����������ƶ�һ���ڵ㣬Ȼ�󷵻ص�ǰ�ڵ������
template<typename T>
inline T& CLinker<T>::GetNext()
{
	ASSERT(0 != m_nCount);
	//����ǰ�ڵ�ΪNULL������Ϊ���һ���ڵ�
	//��ǰ�ڵ�ΪNULL��ʾɾ����ͷ�ڵ�
	if((NULL == m_pNodeCurr) || (NULL == m_pNodeCurr->next))
		m_pNodeCurr = m_pNodeHead;
	else
		m_pNodeCurr = m_pNodeCurr->next;

	return m_pNodeCurr->data;
}

#endif