#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H
#include "..\Common\HandleException.h"

template <class T>
struct BTreeNode{
	T data;
	BTreeNode<T>* left;
	BTreeNode<T>* right;

	BTreeNode(
		T data = T(),
		BTreeNode<T>* left = NULL,
		BTreeNode<T>* right = NULL
	): data(data), left(left), right(right) {}
};

template<class T> class BTreeTraverse;

template<class T> 
class BinaryTree{
	friend class BTreeTraverse<T>;
public:
	BinaryTree(BTreeNode<T>* point = NULL): root(point) {}
	virtual ~BinaryTree() { DeleteTree(root); }
protected:
	BTreeNode<T>* root;
	enum Sibling{Left, Right}; // 标识是找左兄弟还是右兄弟

	bool isEmpty() const; // 判断二叉树是否为空
	BTreeNode<T>* GetParent(BTreeNode<T>* root, const BTreeNode<T>* current)const;
	void DeleteTree(BTreeNode<T>* root);	
	BTreeNode<T>* GetSibling( const Sibling sib, const BTreeNode<T>* current) const;
	void GetNodesCount(const BTreeNode<T>* current, unsigned int* ulCount) const;
	void GetLeafCount(const BTreeNode<T>* current, unsigned int* ulCount) const;
public:
	unsigned int GetDepth(const BTreeNode<T>* current) const;//获得二叉树的深度
	unsigned int GetNodesCount()const;//获得二叉树节点个数
	unsigned int GetLeafCount() const;//获得叶子节点个数
	BTreeNode<T>* Parent(const BTreeNode<T>* current) const;
	BTreeNode<T>* LeftSibling(const BTreeNode<T>* current) const;
	BTreeNode<T>* RightSibling(const BTreeNode<T>* current) const;

	virtual void Insert(const T &data) {}
	virtual void Delete(const T &data) {}
};

template<class T>
void BinaryTree<T>::GetLeafCount( 
	const BTreeNode<T>* current, 
	unsigned int* ulCount ) const
{
	if(current){
		if((current->left == NULL) && (current->right == NULL))//叶子结点
			(*ulCount)++;
		GetLeafCount(current->left, ulCount);
		GetLeafCount(current->right, ulCount);
	}
}

template<class T>
unsigned int BinaryTree<T>::GetLeafCount() const
{
	unsigned int Count = 0;
	GetLeafCount(root, &Count);
	return Count;
}

template<class T>
void BinaryTree<T>::GetNodesCount( 
	const BTreeNode<T>* current, 
	unsigned int* ulCount ) const
{
	unsigned int LeftCount;
	unsigned int RightCount;

	if(NULL == current)
		*ulCount = 0;
	else if ((NULL == current->left) && (NULL == current->right))//叶子结点
		*ulCount = 1;
	else{
		GetNodesCount(current->left, &LeftCount);
		GetNodesCount(current->right, &RightCount);
		*ulCount = 1 + LeftCount +RightCount;
	}
}

template<class T>
unsigned int BinaryTree<T>::GetNodesCount() const
{
	unsigned int ulCount = 0;
	GetNodesCount(root, &ulCount);
	return ulCount;
}

template<class T>
unsigned int BinaryTree<T>::GetDepth( const BTreeNode<T>* current ) const
{
	unsigned int LeftDepth = 0;
	unsigned int RightDepth = 0;
	//Recursion Version
	if(current){
		LeftDepth = GetDepth(current->left);
		RightDepth = GetDepth(current->right);
		return 1 + (LeftDepth > RightDepth ? LeftDepth : RightDepth);
	}else
		return 0;
}

template<class T>
void BinaryTree<T>::DeleteTree( BTreeNode<T>* p )
{
	//以后序周游的方式删除二叉树或其子树
	if(p){
		DeleteTree(p->left); //递归删除左子树
		DeleteTree(p->right); //递归删除右子树
		delete p; 
	}
}

template<class T>
BTreeNode<T>* BinaryTree<T>::GetSibling( 
	const Sibling sib, 
	const BTreeNode<T>* current ) const
{
	if(current == NULL)//defensive coding
		return NULL;

	//返回current结点的父结点
	BTreeNode<T>* temp = Parent(current);
	//如果父结点为空:为根结点
	if(temp==NULL)
		return NULL;
	else if(sib == Left && temp->left != current)//获取左兄弟
		return temp->left;
	else if(sib == Right && temp->right != current )//获取右兄弟
		return temp->right;
	else
		return NULL;
}

template<class T>
BTreeNode<T>* BinaryTree<T>::RightSibling( 
	const BTreeNode<T>* current ) const
{   
	//如果current不为空
	return GetSibling(Right, current);
}

template<class T>
BTreeNode<T>* BinaryTree<T>::LeftSibling( 
	const BTreeNode<T>* current )const
{
	return GetSibling(Left, current);
}

template<class T>
BTreeNode<T>* BinaryTree<T>::Parent( 
	const BTreeNode<T>* current )const
{
	//返回current结点的父结点指针
	if(current == NULL || current == root)
		return NULL; // 空结点或者current为根结点则没有父结点
	//调用递归函数寻找父结点
	return GetParent(root, current);
}

template<class T>
BTreeNode<T>* BinaryTree<T>::GetParent( 
	BTreeNode<T>* root, 
	const BTreeNode<T>* current ) const
{
	//从二叉树的root结点开始，查找current结点
	BTreeNode<T>* temp; // 父结点
	if(root == NULL) //defensive coding
		return NULL;

	//如果父结点为根结点
	if(root->left == current || root->right == current)
		return root;
	//递归寻找父结点
	if((temp = GetParent(root->left, current))!= NULL)
		return temp;
	else return GetParent(root->right, current);
}

template<class T>
bool BinaryTree<T>::isEmpty() const
{
	return ((root)?true:false);
}

#endif