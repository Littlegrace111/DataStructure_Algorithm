#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "..\Common\HandleException.h"
#include "..\Common\MemoryLeakTest.h"
#include "..\LinkerList\Queue.h"
#include "..\LinkerList\Stack.h"

template<typename T>
struct CBTNode{
	T data;
	//CBTNode<T> *parent;
	CBTNode<T> *left;
	CBTNode<T> *right;
	CBTNode(
		T data = T(),
		//CBTNode<T> *parent = NULL,
		CBTNode<T> *left = NULL,
		CBTNode<T> *right = NULL
	): data(data), /*parent(parent),*/ left(left), right(right) {}
};

//通常情况下来讲：二叉树的周游，前序的效率是最高的，能用前序的尽量使用前序，
//效率由高到低：前序->中序->后序
template<typename T>
class CBTree{
public:
	CBTree():m_pNodeRoot(NULL){}
	explicit CBTree(T array[], int size)
	{
		m_pNodeRoot = CreateBinaryTree(array, 0, size);
	}

	virtual ~CBTree(){
		DestroyNode(m_pNodeRoot);
		m_pNodeRoot = NULL;
	};
protected:
	CBTNode<T> *m_pNodeRoot;
	void DestroyNode(CBTNode<T>* p);
	//用于二叉树周游的通用框架：统一支持前序，中序，后序
	enum Order{Pre, In, Post};
	//////////////////////////////////////////////////////
	//非递归版本
	void PreOrderTraverseWithoutRecursion(
		const CBTNode<T> *root,
		void (*Visit)(const T &data)
	)const;

	void InOrderTraverseWithoutRecursion(
		const CBTNode<T> *root,
		void (*Visit)(const T &data)
	)const;

	void PostOrderTraverseWithoutRecursion(
		const CBTNode<T> *root,
		void (*Visit)(const T &data)
	)const;
	//////////////////////////////////////////////////////
	//非递归周游的通用框架
	/*Trace标识位：
	* Left: 标识此节点已经周游完其左子树;
	* Right: 标识此节点已经周游完其左子树和右子树;*/
	enum Tags{Left, Right};
	/*定义栈中的内容：pointer和tags*/
	template<typename T>
	struct StackElement{
		CBTNode<T>* pointer;
		Tags tag;
		StackElement():pointer(NULL), tag(Left){}
		~StackElement(){}
	};
	void TraverseWithoutRecursion(
		const Order order,
		const CBTNode<T>* root,
		void (*Visit)(const T &data)
	)const;

	//////////////////////////////////////////////////////
	//递归版本
	void PreOrderTraverse(
		const CBTNode<T> *p,
		void (*Visit)(const T &data)
	)const;

	void InOrderTraverse(
		const CBTNode<T> *p,
		void (*Visit)(const T &data)
	)const;

	void PostOrderTraverse(
		const CBTNode<T> *p,
		void (*Visit)(const T &data)
	)const;
	/////////////////////////////////////////////////////////
	//递归周游的通用框架
	void Traverse(
		const Order order,
		const CBTNode<T> *p,
		void (*Visit)(const T &data)
	)const;
	/////////////////////////////////////////////////////////
	//广度优先周游
	void LevelOrderTraverse(
		const CBTNode<T>* p,
		void (*Visit)(const T &data)
	)const;
	//获得二叉树的深度
	unsigned int GetDepth(const CBTNode<T>* p) const;
	//获得二叉树节点个数
	void GetNodesCount(
		const CBTNode<T> *p,
		unsigned int *unCount
	)const;
	//获得叶子节点个数
	void GetLeafCount(
		const CBTNode<T> *p,
		unsigned int *unCount
	)const;
    //获得父节点
	CBTNode<T>* GetParent(CBTNode<T>* p, CBTNode<T>* current);

public:
	CBTNode<T>* CreateBinaryTree(const T array[], int i, int size);

	/////////////////////////////////////////////////////////////////
	void PreOrderTraverseWithoutRecursion(void (*Visit)(const T &data))
	{
		PreOrderTraverseWithoutRecursion(m_pNodeRoot, Visit);
		//TraverseWithoutRecursion(Pre, m_pNodeRoot, Visit);
	}
	void InOrderTraverseWithoutRecursion(void (*Visit)(const T &data))
	{
		//InOrderTraverseWithoutRecursion(m_pNodeRoot, Visit);
		TraverseWithoutRecursion(In, m_pNodeRoot, Visit);
	}
	void PostOrderTraverseWithoutRecursion(void (*Visit)(const T &data))
	{
		//PostOrderTraverseWithoutRecursion(m_pNodeRoot, Visit);
		TraverseWithoutRecursion(Post, m_pNodeRoot, Visit);
	}
	/////////////////////////////////////////////////////////////////
	void PreOrderTraverse(void (*Visit)(const T &data))
	{ 
		//PreOrderTraverse(m_pNodeRoot, Visit); 
		Traverse(Pre, m_pNodeRoot, Visit);
	}
	void InOrderTraverse(void (*Visit)(const T &data))
	{ 
		//InOrderTraverse(m_pNodeRoot, Visit); 
		Traverse(In, m_pNodeRoot, Visit);
	}
	void PostOrderTraverse(void (*Visit)(const T &data))
	{ 
		//PostOrderTraverse(m_pNodeRoot, Visit); 
		Traverse(Post, m_pNodeRoot, Visit);
	}
	/////////////////////////////////////////////////////////////////
	//广度优先遍历
	void LevelOrderTraverse(void (*Visit)(const T &data))
	{
		LevelOrderTraverse(m_pNodeRoot, Visit);
	}

	unsigned int GetDepth() const { return GetDepth(m_pNodeRoot); }
	unsigned int GetNodesCount() const 
	{
		unsigned int Count = 0;
		GetNodesCount(m_pNodeRoot, &Count);
		return Count;
	} 
	unsigned int GetLeafCount() const
	{
		unsigned int Count = 0;
		GetLeafCount(m_pNodeRoot, &Count);
		return Count;
	}
};

template<typename T>
inline CBTNode<T>* CBTree<T>::GetParent(CBTNode<T>* p, CBTNode<T>* current)
{
	try{
		if(NULL == p)
			throw MyException("the tree is empty");
		CBTNode<T>* pTemp = NULL;
		//若为根节点
		if(current->data == pTemp->data)//根节点没有父节点
			return NULL;
        //找到父节点
		if(current->data == p->left->data ||
		   current->data == p->right->data)
		   return p;
		if((pTemp = GetParent(p->left, current)) != NULL)
			return pTemp;
		else return GetParent(p->right, current);
    }
	catch(MyException& e){
		cout<<e.GetErrorInfo()<<endl;
		return NULL;
	}
}

template<typename T>
inline void CBTree<T>::DestroyNode( CBTNode<T>* p )
{
	if(p){
		DestroyNode(p->left);
		DestroyNode(p->right);
		delete p;
	}
}

template<typename T>
inline void CBTree<T>::GetLeafCount( 
	const CBTNode<T>* p, 
	unsigned int *unCount ) const
{
	ASSERT(unCount);
	if(p){
		if((NULL == p->left) && (NULL == p->right))
			++(*unCount);
		GetLeafCount(p->left, unCount);
		GetLeafCount(p->right, unCount);
	}
}

template<typename T>
inline void CBTree<T>::GetNodesCount( 
	const CBTNode<T> *p, 
	unsigned int *unCount ) const
{
	ASSERT(unCount);

	unsigned int LeftCount;
	unsigned int RightCount;

	if(NULL == p)
		*unCount = 0;
	else if ((NULL == p->left) && (NULL == p->right))
		*unCount = 1;
	else{
		GetNodesCount(p->left, &LeftCount);
		GetNodesCount(p->right, &RightCount);
		*unCount = 1 + LeftCount +RightCount;
	}
}

template<typename T>
inline unsigned int CBTree<T>::GetDepth( const CBTNode<T>* p ) const
{
	 unsigned int LeftDepth;
	 unsigned int RightDepth;

	 if(p){
		 LeftDepth = GetDepth(p->left);
		 RightDepth = GetDepth(p->right);
		 return 1 + (LeftDepth > RightDepth ? LeftDepth : RightDepth);
	 }else
		 return 0;
}

///////////////////////////////////////////////////////////////
//广度优先周游
//根节点入队；
//队列不为空，访问队首，队首出队，左子树和右子树入队；
//依次上面的步骤直到为空；
template<typename T>
inline void CBTree<T>::LevelOrderTraverse(
	const CBTNode<T>* p,
	void (*Visit)(const T &data))const
{
	CQueue<CBTNode<T>*> aQueue;
	CBTNode<T>* pointer = const_cast<CBTNode<T>*>(p);
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
template<typename T>
inline void CBTree<T>::Traverse(
	const Order order,
	const CBTNode<T>* p,
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
template<typename T>
inline void CBTree<T>::TraverseWithoutRecursion(
	const Order order,
	const CBTNode<T>* root,
	void (*Visit)(const T &data) )const
{
	StackElement<T> element;
	CStack<StackElement<T> > aStack;
	CBTNode<T>* pointer = const_cast<CBTNode<T>*>(root);
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
template<typename T>
inline void CBTree<T>::PreOrderTraverseWithoutRecursion( 
	const CBTNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	CStack<CBTNode<T>* > aStack;
	CBTNode<T>* pointer = const_cast<CBTNode<T>* >(root);
	
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
template<typename T>
inline void CBTree<T>::InOrderTraverseWithoutRecursion( 
	const CBTNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	CStack<CBTNode<T>* > aStack;
	CBTNode<T>* pointer = const_cast<CBTNode<T>* >(root);

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

template<typename T>
inline void CBTree<T>::PostOrderTraverseWithoutRecursion( 
	const CBTNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	StackElement<T> element;
	CStack<StackElement<T> > aStack;
	CBTNode<T>* pointer = const_cast<CBTNode<T>*>(root);
	//教科书经典实现版本，千锤百炼
	//while(true)//进入左子树
	//{
	//	while(NULL != pointer)
	//	{
	//		element.pointer = pointer;
	//		element.tag = Left;
	//		aStack.push(element);
	//		pointer = pointer->left;//沿着左子树方向向下周游
	//	}
	//    aStack.pop(element);
	//	pointer = element.pointer;
	//	//从右子树回来
	//	while(Right == element.tag)
	//	{
	//		Visit(pointer->data);
	//		if(aStack.IsEmpty())
	//	        return;
	//        aStack.pop(element);
 //           pointer = element.pointer;
	//	}
 //       //从左子树回来
 //       element.tag = Right;
 //       aStack.push(element);
 //       pointer = pointer->right;
	//}

	//自己很渣的实现版本：
	//算法真是博大精深，自己最后不断优化，竟然成了原来教科书上的版本
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

template<typename T>
inline void CBTree<T>::PostOrderTraverse( 
	const CBTNode<T> *p, 
	void (*Visit)(const T &data) ) const
{
	if(p)
	{
		PostOrderTraverse(p->left, Visit);
		PostOrderTraverse(p->right, Visit);
		Visit(p->data);
	}
}

template<typename T>
inline void CBTree<T>::InOrderTraverse( 
	const CBTNode<T> *p, 
	void (*Visit)(const T &data) ) const
{
	if(p)
	{
		InOrderTraverse(p->left, Visit);
		Visit(p->data);
		InOrderTraverse(p->right, Visit);
	}
}

template<typename T>
inline void CBTree<T>::PreOrderTraverse( 
	const CBTNode<T> *p, 
	void (*Visit)(const T &data) ) const
{
	if(p)
	{
		Visit(p->data);
		PreOrderTraverse(p->left, Visit);
		PreOrderTraverse(p->right, Visit);
	}
}

template<typename T>
inline CBTNode<T>* CBTree<T>::CreateBinaryTree(
	const T array[], int i, int size )
{
	if(i >= size) return NULL;
	CBTNode<T>* pNewNode = NULL;
	pNewNode = new CBTNode<T>;
	pNewNode->data = array[i];
	pNewNode->left = CreateBinaryTree(array, 2*i+1, size);
	pNewNode->right = CreateBinaryTree(array, 2*i+2, size);
	return pNewNode;
}


#endif