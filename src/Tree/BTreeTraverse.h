#ifndef _BTREE_TRAVERSE_H
#define _BTREE_TRAVERSE_H
#include "..\LinkerList\Queue.h"
#include "..\LinkerList\Stack.h"
#include "BinaryTree.h"

//decalaration
template<class T> class BinaryTree;

//Visit回调函数
template<class T>
void PrintElement(const T &data)
{
	std::cout<<data;
}

template<class T>
class BTreeTraverse /*: public BinaryTree<T>*/{
	friend class BinaryTree<T>;
public:
	//BTreeTraverse(BTreeNode<T>* current): BinaryTree(current) {}
	//~BTreeTraverse() {}
private:
	//用于二叉树周游的通用框架：统一支持前序，中序，后序
	enum Order{Pre, In, Post};
	//递归周游的通用框架
	void Traverse(
		const Order order,
		const BTreeNode<T> *p,
		void (*Visit)(const T &data)
		)const;

	//非递归版本
	void PreOrderTraverseWithoutRecursion(
		const BTreeNode<T> *root,
		void (*Visit)(const T &data)
	)const;

	void InOrderTraverseWithoutRecursion(
		const BTreeNode<T> *root,
		void (*Visit)(const T &data)
	)const;

	void PostOrderTraverseWithoutRecursion(
		const BTreeNode<T> *root,
		void (*Visit)(const T &data)
	)const;

	//非递归周游的通用框架
	/*Trace标识位：
	* Left: 标识此节点已经周游完其左子树;
	* Right: 标识此节点已经周游完其左子树和右子树;*/
	enum Tags{Left, Right};
	/*定义栈中的内容：pointer和tags*/
	template<typename T>
	struct StackElement{
		BTreeNode<T>* pointer;
		Tags tag;
		StackElement():pointer(NULL), tag(Left){}
		~StackElement(){}
	};
	void TraverseWithoutRecursion(
		const Order order,
		const BTreeNode<T>* root,
		void (*Visit)(const T &data)
	)const;

	//广度优先周游
	void LevelOrderTraverse(
		const BTreeNode<T>* p,
		void (*Visit)(const T &data)
	)const;

public:
	void PreOrderTraverseWithoutRecursion(BinaryTree<T> &tree, void (*Visit)(const T &data))
	{
		PreOrderTraverseWithoutRecursion(tree.root, Visit);
		//TraverseWithoutRecursion(Pre, m_pNodeRoot, Visit);
	}
	void InOrderTraverseWithoutRecursion(BinaryTree<T> &tree, void (*Visit)(const T &data))
	{
		//InOrderTraverseWithoutRecursion(m_pNodeRoot, Visit);
		TraverseWithoutRecursion(In, tree.root, Visit);
	}
	void PostOrderTraverseWithoutRecursion(BinaryTree<T> &tree, void (*Visit)(const T &data))
	{
		//PostOrderTraverseWithoutRecursion(m_pNodeRoot, Visit);
		TraverseWithoutRecursion(Post, tree.root, Visit);
	}
	
	void PreOrderTraverse(BinaryTree<T> &tree, void (*Visit)(const T &data))
	{ 
		//PreOrderTraverse(m_pNodeRoot, Visit); 
		Traverse(Pre, tree.root, Visit);
	}
	void InOrderTraverse(BinaryTree<T> &tree, void (*Visit)(const T &data))
	{ 
		//InOrderTraverse(m_pNodeRoot, Visit); 
		Traverse(In, tree.root, Visit);
	}
	void PostOrderTraverse(BinaryTree<T> &tree, void (*Visit)(const T &data))
	{ 
		//PostOrderTraverse(m_pNodeRoot, Visit); 
		Traverse(Post, tree.root, Visit);
	}

	//广度优先遍历
	void LevelOrderTraverse(BinaryTree<T> &tree, void (*Visit)(const T &data))
	{
		LevelOrderTraverse(tree.root, Visit);
	}
};

//广度优先周游：
//根节点入队；
//队列不为空，访问队首，队首出队，左子树和右子树入队；
//依次上面的步骤直到为空；
template<class T>
inline void BTreeTraverse<T>::LevelOrderTraverse(
	const BTreeNode<T>* p,
	void (*Visit)(const T &data))const
{
	CQueue<BTreeNode<T>*> aQueue;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>*>(p);
	aQueue.EnQueue(pointer); //根节点入队
	while(!aQueue.IsEmpty()){
		pointer = aQueue.GetFront(); //取队列首节点
		Visit(pointer->data);
		aQueue.DeQueue();
		if(pointer->left)
			aQueue.EnQueue(pointer->left);
		if(pointer->right)
			aQueue.EnQueue(pointer->right);
	}
}

//递归周游的通用框架
template<class T>
inline void BTreeTraverse<T>::Traverse(
	const Order order,
	const BTreeNode<T>* p,
	void (*Visit)(const T &data) )const
{
	if(p){
		if(Pre == order) Visit(p->data);//前序
		Traverse(order, p->left, Visit);
		if(In == order) Visit(p->data);//中序
		Traverse(order, p->right, Visit);
		if(Post == order) Visit(p->data);//后序
	}
}

//非递归周游的通用框架
template<class T>
inline void BTreeTraverse<T>::TraverseWithoutRecursion(
	const Order order,
	const BTreeNode<T>* root,
	void (*Visit)(const T &data) )const
{
	StackElement<T> element;
	CStack<StackElement<T> > aStack;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>*>(root);
	while(true){//栈空的时候结束循环
		while(pointer){//遍历左子树
			element.pointer = pointer;
			element.tag = Left;
			aStack.push(element);
			if(Pre == order) //前序遍历在此访问节点
				Visit(pointer->data);
			pointer = pointer->left;
		}
		//栈顶元素弹栈
		aStack.pop(element);
		pointer = element.pointer;
		//右子树遍历完，弹栈
		while(Right == element.tag){
			if(Post == order)
				Visit(pointer->data);
			if(aStack.IsEmpty())
				return;
			aStack.pop(element);
			pointer = element.pointer;
		}
		//左子树遍历完遍历右子树
		if(Left == element.tag){
			element.tag = Right;
			aStack.push(element);
			if(In == order) //中序在此访问节点
				Visit(pointer->data);
			pointer = pointer->right;
		}
	}
}

////////////////////////////////////////////////////////////
/*非递归前序周游二叉树
* 1. 遇到一个节点，访问该节点，并推出栈中;
* 2. 下降周游其左子树;
* 3. 一直周游到叶子节点，从栈顶弹出节点;
* 4. 并按照它的右链指示周游该节点的右子树;
*/
template<class T>
inline void BTreeTraverse<T>::PreOrderTraverseWithoutRecursion( 
	const BTreeNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	CStack<BTreeNode<T>* > aStack;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>* >(root);

	//// 教程书的经典实现版本：
	//while(!aStack.IsEmpty() || pointer)
	//{
	//	if(pointer)
	//	{
	//		Visit(pointer->data);
	//		aStack.push(pointer);
	//		pointer = pointer->left;
	//	}else{//说明到达叶子节点的下一个节点
	//		aStack.pop(pointer);//回溯到上一个节点
	//		pointer = pointer->right;
	//	}
	//}
	//但是，前序还可以再进行优化
	//核心思想是：由于栈中存储的是将来需要访问的节点，那么
	//已经访问的节点没有必要存入栈中，减少栈中存储的元素和减少入栈出栈的操作
	while(true){
		while(pointer){
			Visit(pointer->data);
			if(pointer->right)
				aStack.push(pointer->right);
			pointer = pointer->left;
		}
		if(aStack.IsEmpty())
			return;
		else
			aStack.pop(pointer);
	}
}

/*非递归中序周游二叉树
* 1. 遇到一个节点，推出栈中；
* 2. 周游其左子树；
* 3. 周游完左子树，弹出栈顶元素，访问之;
* 4. 周游其右子树
*/
template<class T>
inline void BTreeTraverse<T>::InOrderTraverseWithoutRecursion( 
	const BTreeNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	CStack<BTreeNode<T>* > aStack;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>* >(root);

	//这是我自己实现的版本
	while(true)
	{
		if(pointer)
		{
			aStack.push(pointer);
			pointer = pointer->left;
		}else{
			if(aStack.IsEmpty())
				return;
			aStack.pop(pointer);
			Visit(pointer->data);
			pointer = pointer->right;
		}
	}
}

template<class T>
inline void BTreeTraverse<T>::PostOrderTraverseWithoutRecursion( 
	const BTreeNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	StackElement<T> element;
	CStack<StackElement<T> > aStack;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>*>(root);

	while(true){
		//最开始遍历左子树
		while(pointer){
			element.pointer = pointer;
			element.tag = Left;
			aStack.push(element);
			pointer = pointer->left;
		}
		//左子树遍历完毕，栈顶元素弹栈
		aStack.pop(element);
		pointer = element.pointer;
		//这时候最开始元素为Left遍历
		while(element.tag == Right){
			Visit(pointer->data);
			if(aStack.IsEmpty())//直到栈为空
				return;
			aStack.pop(element);
			pointer = element.pointer;
		}

		if(element.tag == Left){
			element.tag = Right;
			aStack.push(element);
			pointer = pointer->right;
		}
	}
}

#endif