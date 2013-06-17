#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H
#include "..\Common\HandleException.h"

template<typename T>
class CBSTree: public CBTree<T>{
public:
	CBSTree() {}
	CBSTree(T array[], int size)
		:CBTree(array, size) { m_pNodeRoot = CreateBinaryTree(array, 0, size); }
protected:
	CBTNode<T>* CreateNewNode(const T &data);
	virtual CBTNode<T>* InsertNode(const T &data, CBTNode<T>* p);
	virtual CBTNode<T>* DeleteNode(const T &data, CBTNode<T>* p);
	CBTNode<T>* FindMin(CBTNode<T>* p);
	CBTNode<T>* FindMax(CBTNode<T>* p);
	void InsertNodeWithoutRecursion(const T &data);	
	void DeleteNodeWithoutRecursion(const T &data);
public:
	void Insert(const T &data){ InsertNodeWithoutRecursion(data); }
	void Delete(const T &data){ DeleteNode(data, m_pNodeRoot); }
};

//�ǵݹ���㷨���
//�ڶ��������������ڵ�Ϊ�������ұߵĽڵ�
template<typename T>
inline CBTNode<T>* CBSTree<T>::FindMax( CBTNode<T>* p )
{
	while(p->right)
		p = p->right;
	return p;
}

//�ݹ���㷨���
//ͬ����������������ߵĽڵ�Ϊ������С�ڵ�
template<typename T>
inline CBTNode<T>* CBSTree<T>::FindMin( CBTNode<T>* p )
{
	if(NULL == p->left)
		return p;
	else 
		return FindMin(p->left);
}

//�����������ĵݹ�ɾ�����:
//1. �½����β���Ҫɾ���Ľ��p��
//2. ���������Ҷ��������ɾ����
//   �������һ����Ҷ�����丸�������ƹ��ý��ָ������ӽ�㣬Ȼ��ý�㱻ɾ����
//   ��������������Թ�Ϊһ�ࣻ
//3. �����������ӵĽ�㣺
//   ɾ������һ��������������С��㣨Ҳ��������ݹ�ĵ�һ����㣩����ý������ݲ��ݹ�ɾ���Ǹ����;
//             ��Ϊ�������е���С��㲻����������ӣ����Եڶ���ɾ������˻�����һ�������
//   ɾ�����Զ���ͬ����������������㣨Ҳ��������ݹ�����һ����㣩����ý������ݲ��ݹ�ɾ���Ǹ���㣻
//   ��ɾ���㷨��ƽ�������Եõ��Ľ�
template<typename T>
inline CBTNode<T>* CBSTree<T>::DeleteNode( const T &data, CBTNode<T>* p)
{
	CBTNode<T>* pTemp = NULL;
	if(data < p->data)
		p->left = DeleteNode(data, p->left);
	else if (data > p->data)
		p->right = DeleteNode(data, p->right);
	else if( p->left && p->right){
		pTemp = FindMin(p->right);//replace with smallest in right subtree
		p->data = pTemp->data;
		p->right = DeleteNode(p->data, p->right);
	}else{//One or zero children
		MYTRACE("delte node %d succeeded!", p->data);
		pTemp = p;
		if(NULL == p->left)
			p = p->right;
		else if(NULL == p->right)
			p = p->left;
		free(pTemp);
	}
	return p;

}

template<typename T>
inline CBTNode<T>* CBSTree<T>::CreateNewNode( const T &data )
{
	CBTNode<T>* pNewNode = new CBTNode<T>;
	pNewNode->data = data;
	return pNewNode;
}

//�����������ķǵݹ�汾
template<typename T>
inline void CBSTree<T>::InsertNodeWithoutRecursion( 
	const T &data )
{
	if(NULL == m_pNodeRoot){
		MYTRACE("empty bianry search tree, create root node.");
		m_pNodeRoot = CreateNewNode(data);
		return;
	}

	CBTNode<T>* pointer = m_pNodeRoot;
	while(true){
		if(data < pointer->data){//������
			if(NULL == pointer->left){
				MYTRACE("insert left node.");
				pointer->left = CreateNewNode(data);
				break; 
			}else{
				MYTRACE("go to left node");
				pointer = pointer->left;
			}
		}else if (data > pointer->data){//������
			if(NULL == pointer->right){
				MYTRACE("insert right node.");
				pointer->right = CreateNewNode(data);
				break; 
			}else{
				MYTRACE("go to right node");
				pointer = pointer->right;
			}
		}else // if equal, do nothing
			break;
	}
	return;
}

//////////////////////////////////////////////////////
//�ݹ�汾
//�������½ڵ�Ĺؼ����������ڵ�Ĺؼ�����бȽ�
//��������Ľڵ�Ĺؼ���С������������������
//��������Ľڵ�Ĺؼ����������������������
//���������������������бȽϣ�ֱ�����½ڵ���ΪҶ�ӽڵ���뵽��������
template<typename T>
inline CBTNode<T>* CBSTree<T>::InsertNode( 
	const T &data, CBTNode<T>* p )
{
	if(NULL == p){
		CBTNode<T>* pNewNode = new CBTNode<T>;
		pNewNode->data = data;
		p = pNewNode;
	}else if(data < p->data) {//������
		MYTRACE("go to left child tree");
		p->left = InsertNode(data, p->left);
	}else if(data > p->data) {//������
		MYTRACE("go to right child tree");
		p->right = InsertNode(data, p->right);
	}
	return p;
}

#endif