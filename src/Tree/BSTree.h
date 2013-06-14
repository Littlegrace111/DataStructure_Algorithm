#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H
#include "..\Common\HandleException.h"

template<typename T>
class CBSTree: public CBTree<T>{
public:
	CBSTree() {}
	CBSTree(T array[], int size)
		:CBTree(array, size) { m_pNodeRoot = CreateBinaryTree(array, 0, size); }

private:
	CBTNode<T>* CreateNewNode(const T &data);
	CBTNode<T>* InsertNode(const T &data, CBTNode<T>* p);
	CBTNode<T>* DeleteNode(const T &data, CBTNode<T>* p);
	CBTNode<T>* FindMin(CBTNode<T>* p);
	CBTNode<T>* FindMax(CBTNode<T>* p);

public:
	//�ݹ�汾
	void InsertNode(const T &data)
	{ 
		InsertNodeWithoutRecursion(data);
	}

	void InsertNodeWithoutRecursion(const T &data);
	CBTNode<T>* DeleteNodeEx(const T &data, CBTNode<T>* p);
	void DeleteNode(const T &data, CBTNode<T>* p);
};

template<typename T>
inline void CBSTree<T>::DeleteNode( const T &data, CBTNode<T>* p )
{
	try{
		//if(NULL == p)
			//throw MyException("data not find!");
		//begin of the right precess
		//MYTRACE("start the delete node:");

	}
	catch(MyException& e){
		cout<<"DeleteNode: "<<e.GetErrorInfo()<<endl;
		return NULL;
	}
}

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

//�����������ĵݹ�ɾ�����
//1. �½������ҵ�Ҫɾ���Ľ��p��
//2. ��p
template<typename T>
inline CBTNode<T>* CBSTree<T>::DeleteNodeEx( const T &data, CBTNode<T>* p)
{
	CBTNode<T>* pointer = NULL;
	try{
		if(NULL == p)
			throw MyException("data not find!");
		if(data < p->data)
			p->left = DeleteNode(data, p->left);
		else if (data > p->data)
			p->right = DeleteNode(data, p->right);
		else if( p->left && p->right){
			pointer = FindMin(p->right);//�ҵ�����������С�Ľڵ�
			p->data = pointer->data;
			p->right = DeleteNode(p->data, p->right);
		}else{//One or zero children
			pointer = p;
			if(NULL == pointer->left)
				pointer = pointer->right;
			else if(NULL == pointer->right)
				pointer = pointer->left;
			MYTRACE("delte node %d succeeded!", p->data);
			free(pointer);
		}
		return p;
	}
	catch(MyException& e){
		cout<<"DeleteNodeEx: "<<e.GetErrorInfo()<<endl;
		return NULL;
	}
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