#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include "..\Common\HandleException.h"
#include "BinaryTree.h"

template<typename T>
class BSearchTree: public BinaryTree<T>{
public:
	BSearchTree() {}
    ~BSearchTree(){}

protected:
	BTreeNode<T>* CreateNewNode(const T &data);
	virtual BTreeNode<T>* InsertNode(const T &data, BTreeNode<T>* p);
	virtual BTreeNode<T>* DeleteNode(const T &data, BTreeNode<T>* p);
	BTreeNode<T>* FindMin(BTreeNode<T>* p);
	BTreeNode<T>* FindMax(BTreeNode<T>* p);
	void InsertNodeWithoutRecursion(const T &data);	
	void DeleteNodeWithoutRecursion(const T &data);

public:
	void Insert(const T &data){ InsertNodeWithoutRecursion(data); }
	void Delete(const T &data){ DeleteNode(data, root); }
};

template<typename T>
inline void BSearchTree<T>::DeleteNodeWithoutRecursion( const T &data )
{

}

//非递归的算法框架
//在二叉搜索树的最大节点为此树最右边的节点
template<typename T>
inline BTreeNode<T>* BSearchTree<T>::FindMax( BTreeNode<T>* p )
{
	while(p->right)
		p = p->right;
	return p;
}

//递归的算法框架
//同理，二叉搜索树最左边的节点为此树最小节点
template<typename T>
inline BTreeNode<T>* BSearchTree<T>::FindMin( BTreeNode<T>* p )
{
	if(NULL == p->left)
		return p;
	else 
		return FindMin(p->left);
}

//二叉搜索数的递归删除框架:
//1. 下降周游查找要删除的结点p；
//2. 若结点是树叶，则立即删除，
//   若结点有一个树叶，则其父结点可以绕过该结点指向其儿子结点，然后该结点被删除；
//   以上两种情况可以归为一类；
//3. 若有两个儿子的结点：
//   删除策略一：用右子树的最小结点（也就是中序递归的第一个结点）替代该结点的数据并递归删除那个结点;
//             因为右子树中的最小结点不可能有左儿子，所以第二次删除情况退化到第一种情况；
//   删除策略二：同理，用左子树的最大结点（也就是中序递归的最后一个结点）替代该结点的数据并递归删除那个结点；
//   此删除算法在平衡树可以得到改进
template<typename T>
inline BTreeNode<T>* BSearchTree<T>::DeleteNode( const T &data, BTreeNode<T>* p)
{
	//ASSERT(p);//defensive coding

	BTreeNode<T>* pTemp = NULL;
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
inline BTreeNode<T>* BSearchTree<T>::CreateNewNode( const T &data )
{
	BTreeNode<T>* pNewNode = new BTreeNode<T>;
	pNewNode->data = data;
	return pNewNode;
}

//二叉搜索树的非递归版本
template<typename T>
inline void BSearchTree<T>::InsertNodeWithoutRecursion( const T &data )
{
	if(NULL == root){
		MYTRACE("empty bianry search tree, create root node.");
		root = CreateNewNode(data);
		return;
	}

	BTreeNode<T>* pointer = root;
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
inline BTreeNode<T>* BSearchTree<T>::InsertNode( 
	const T &data, BTreeNode<T>* p )
{
	if(root == NULL){//if an empty tree, create root node  and return
		root = CreateNewNode(data);
		return root;
	}

	if(NULL == p){
		p = CreateNewNode(data);
	}else if(data < p->data) {//左子树
		//MYTRACE("go to left child tree");
		p->left = InsertNode(data, p->left);
	}else if(data > p->data) {//右子树
		//MYTRACE("go to right child tree");
		p->right = InsertNode(data, p->right);
	}
	return p;
}

#endif