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
	//递归版本
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

//非递归的算法框架
//在二叉搜索树的最大节点为此树最右边的节点
template<typename T>
inline CBTNode<T>* CBSTree<T>::FindMax( CBTNode<T>* p )
{
	while(p->right)
		p = p->right;
	return p;
}

//递归的算法框架
//同理，二叉搜索树最左边的节点为此树最小节点
template<typename T>
inline CBTNode<T>* CBSTree<T>::FindMin( CBTNode<T>* p )
{
	if(NULL == p->left)
		return p;
	else 
		return FindMin(p->left);
}

//二叉搜索数的递归删除框架
//1. 下降周游找到要删除的结点p；
//2. 若p
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
			pointer = FindMin(p->right);//找到右子树中最小的节点
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

//二叉搜索树的非递归版本
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
		if(data < pointer->data){//左子树
			if(NULL == pointer->left){
				MYTRACE("insert left node.");
				pointer->left = CreateNewNode(data);
				break; 
			}else{
				MYTRACE("go to left node");
				pointer = pointer->left;
			}
		}else if (data > pointer->data){//右子树
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
//递归版本
//将插入新节点的关键码与树根节点的关键码进行比较
//若待插入的节点的关键码小于树根，进入左子树
//若待插入的节点的关键码大于树根，进入右子树
//继续在子树里与树根进行比较，直到把新节点作为叶子节点插入到二叉树中
template<typename T>
inline CBTNode<T>* CBSTree<T>::InsertNode( 
	const T &data, CBTNode<T>* p )
{
	if(NULL == p){
		CBTNode<T>* pNewNode = new CBTNode<T>;
		pNewNode->data = data;
		p = pNewNode;
	}else if(data < p->data) {//左子树
		MYTRACE("go to left child tree");
		p->left = InsertNode(data, p->left);
	}else if(data > p->data) {//右子树
		MYTRACE("go to right child tree");
		p->right = InsertNode(data, p->right);
	}
	return p;
}

#endif