#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include "BinaryTree.h"
#include "BSearchTree.h"

template<typename T>
class CAVLTree: public BSearchTree<T>{
private:
	BTreeNode<T>* RightRotate(BTreeNode<T> *a);
	BTreeNode<T>* LeftRotate(BTreeNode<T> *a);
	BTreeNode<T>* LeftRightRotate(BTreeNode<T> *a);
	BTreeNode<T>* RightLeftRotate(BTreeNode<T> *a);
protected:
	BTreeNode<T>* Rotate(const T &data, BTreeNode<T>* p);
	BTreeNode<T>* InsertNode(const T &data, BTreeNode<T>* p);
	BTreeNode<T>* DeleteNode(const T &data, BTreeNode<T>* p);
public:
	void Delete(const T &data) { DeleteNode(data, root);}
	void Insert(const T &data) { InsertNode(data, root);}
};

template<typename T>
inline BTreeNode<T>* CAVLTree<T>::Rotate( const T &data, BTreeNode<T>* p )
{
	int LeftDepth = GetDepth(p->left);
	int RightDepth = GetDepth(p->right);

	if( 2 == LeftDepth - RightDepth){//rotate
		if(data < p->left->data)
			p = LeftRotate(p);
		else
			p = LeftRightRotate(p);
	}else if(2 == RightDepth - LeftDepth){//rotate
		if(data > p->right->data)
			p = RightRotate(p);
		else
			p = RightLeftRotate(p);
	}else {
		//do nothing
	}
	return p;
}

//删除操作：
//1. 定位删除的结点；
//2. 用该结点的右孩子的最左孩子替换该结点(右子树的最小结点)；
//3. 重新调整以该结点为根的子树为AVL树;
template<typename T>
inline BTreeNode<T>* CAVLTree<T>::DeleteNode( const T &data, BTreeNode<T>* p )
{
	if(p == NULL) 
		return NULL;

	if(data == p->data){//allocated the node p
		if(p->right == NULL){
			BTreeNode<T>* pTemp = p;
			p = p->left;
			delete pTemp;
		}else {
			BTreeNode<T>* pTemp = p->right;
			pTemp = FindMin(pTemp);
			p->data = pTemp->data;//just copy the data
			p->right = DeleteNode(p->data, p->right);
		}
		return p;
	}else if(data > p->data){
		DeleteNode(data, p->right);
		if(p->right) 
			Rotate(data, p->right);
	}else {
		DeleteNode(data, p->left);
		if(p->left)
			Rotate(data, p->left);
	}
	//if(p) Rotate(data, p);
}

template<typename T>
inline BTreeNode<T>* CAVLTree<T>::InsertNode( const T &data, BTreeNode<T>* p )
{
	if(root == NULL){//if an empty tree, create root node;
		root = CreateNewNode(data);
		return root;
	}

	if(NULL == p)
	{   //create and return a one-node tree	
		p = CreateNewNode(data);
	}else if(data < p->data){//left child
		p->left = InsertNode(data, p->left);

		int LeftDepth = GetDepth(p->left);
		int RightDepth = GetDepth(p->right);
		if( 2 == LeftDepth - RightDepth){//rotate
			if(data < p->left->data)
				//p = LeftRotate(p);
				p = RightRotate(p);
			else
				//p = LeftRightRotate(p);
				p = RightLeftRotate(p);
		}
	}else if(data > p->data){
		p->right = InsertNode(data, p->right);

		int LeftDepth = GetDepth(p->left);
		int RightDepth = GetDepth(p->right);
		if(2 == RightDepth - LeftDepth){//rotate
			if(data > p->right->data)
				//p = RightRotate(p);
				p = LeftRotate(p);
			else
				//p = RightLeftRotate(p);
				p = LeftRightRotate(p);
		}
	}
	return p;
}

//RL旋转：先B右旋转，后A左旋转
//          B                   A
//         / \                /   \
//        BL  C              B     C
//           / \      =>    / \   / \
//          A   CR         BL AL AR CR
//         / \                   +
//        AL  AR
//            +
// Special flag is used for some kind of delete operation, for example:
//        3                   4
//       / \                 / \
//   (-)2   5      =>       3   5
//         / \                   \
//        4   6                   6
template<typename T>
inline BTreeNode<T>* CAVLTree<T>::RightLeftRotate( BTreeNode<T> *a )
{
	a->right = RightRotate(a->right);
	return LeftRightRotate(a);
}

//LR旋转：先B左旋转，后A右旋转
//          C                   B
//         / \                /   \
//        A   CR             A     C
//       / \         =>     / \   / \
//      AL  B              AL BL BR CR
//         / \                   +
//        BL  BR
//            +
// Special flag is used for some kind of delete operation, for example:
//        4                   3
//       / \                 / \
//      2   5(-)    =>      2   4
//     / \                 /
//    1   3               1
template<typename T>
inline BTreeNode<T>* CAVLTree<T>::LeftRightRotate( BTreeNode<T> *a )
{
	a->left = LeftRotate(a->left);
	return RightRotate(a);
}

//left rotate
//      B               A
//     / \             / \
//    A   BR    =>    AL  B
//   / \              +  / \
//  AL  AR              AR  BR
//  +
template<typename T>
inline BTreeNode<T>* CAVLTree<T>::LeftRotate( BTreeNode<T> *a )
{
	BTreeNode<T>* b = a->right;
    a->right = b->left;
	b->left = a;

	//if root, update root node
	if(a == root){
		root = b;
	}

	return b;
}

//right rotate
//      A                B
//     / \              / \
//    AL  B      =>    A   BR
//       / \          / \  +
//      BL  BR       AL  BL
//          +
template<typename T>
inline BTreeNode<T>* CAVLTree<T>::RightRotate( BTreeNode<T> *a )
{   //rotate
	BTreeNode<T> *b = a->left;
	a->left = b->right;
	b->right = a;

	//if root, update root node
	if(a == root){
		root = b;
	}
	return b;
}

#endif