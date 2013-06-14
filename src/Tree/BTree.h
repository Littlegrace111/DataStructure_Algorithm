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

//ͨ������������������������Σ�ǰ���Ч������ߵģ�����ǰ��ľ���ʹ��ǰ��
//Ч���ɸߵ��ͣ�ǰ��->����->����
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
	//���ڶ��������ε�ͨ�ÿ�ܣ�ͳһ֧��ǰ�����򣬺���
	enum Order{Pre, In, Post};
	//////////////////////////////////////////////////////
	//�ǵݹ�汾
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
	//�ǵݹ����ε�ͨ�ÿ��
	/*Trace��ʶλ��
	* Left: ��ʶ�˽ڵ��Ѿ���������������;
	* Right: ��ʶ�˽ڵ��Ѿ�����������������������;*/
	enum Tags{Left, Right};
	/*����ջ�е����ݣ�pointer��tags*/
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
	//�ݹ�汾
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
	//�ݹ����ε�ͨ�ÿ��
	void Traverse(
		const Order order,
		const CBTNode<T> *p,
		void (*Visit)(const T &data)
	)const;
	/////////////////////////////////////////////////////////
	//�����������
	void LevelOrderTraverse(
		const CBTNode<T>* p,
		void (*Visit)(const T &data)
	)const;
	//��ö����������
	unsigned int GetDepth(const CBTNode<T>* p) const;
	//��ö������ڵ����
	void GetNodesCount(
		const CBTNode<T> *p,
		unsigned int *unCount
	)const;
	//���Ҷ�ӽڵ����
	void GetLeafCount(
		const CBTNode<T> *p,
		unsigned int *unCount
	)const;
    //��ø��ڵ�
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
	//������ȱ���
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
		//��Ϊ���ڵ�
		if(current->data == pTemp->data)//���ڵ�û�и��ڵ�
			return NULL;
        //�ҵ����ڵ�
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
//�����������
//���ڵ���ӣ�
//���в�Ϊ�գ����ʶ��ף����׳��ӣ�����������������ӣ�
//��������Ĳ���ֱ��Ϊ�գ�
template<typename T>
inline void CBTree<T>::LevelOrderTraverse(
	const CBTNode<T>* p,
	void (*Visit)(const T &data))const
{
	CQueue<CBTNode<T>*> aQueue;
	CBTNode<T>* pointer = const_cast<CBTNode<T>*>(p);
	aQueue.EnQueue(pointer); //���ڵ����
	while(!aQueue.IsEmpty()){
		pointer = aQueue.GetFront(); //ȡ�����׽ڵ�
		Visit(pointer->data);
		aQueue.DeQueue();
		if(pointer->left)
			aQueue.EnQueue(pointer->left);
		if(pointer->right)
			aQueue.EnQueue(pointer->right);
	}
}

//�ݹ����ε�ͨ�ÿ��
template<typename T>
inline void CBTree<T>::Traverse(
	const Order order,
	const CBTNode<T>* p,
	void (*Visit)(const T &data) )const
{
	if(p){
		if(Pre == order) Visit(p->data);//ǰ��
		Traverse(order, p->left, Visit);
		if(In == order) Visit(p->data);//����
		Traverse(order, p->right, Visit);
		if(Post == order) Visit(p->data);//����
	}
}

//�ǵݹ����ε�ͨ�ÿ��
template<typename T>
inline void CBTree<T>::TraverseWithoutRecursion(
	const Order order,
	const CBTNode<T>* root,
	void (*Visit)(const T &data) )const
{
	StackElement<T> element;
	CStack<StackElement<T> > aStack;
	CBTNode<T>* pointer = const_cast<CBTNode<T>*>(root);
	while(true){//ջ�յ�ʱ�����ѭ��
		while(pointer){//����������
			element.pointer = pointer;
			element.tag = Left;
			aStack.push(element);
			if(Pre == order) //ǰ������ڴ˷��ʽڵ�
				Visit(pointer->data);
			pointer = pointer->left;
		}
		//ջ��Ԫ�ص�ջ
		aStack.pop(element);
		pointer = element.pointer;
		//�����������꣬��ջ
		while(Right == element.tag){
			if(Post == order)
		        Visit(pointer->data);
		    if(aStack.IsEmpty())
		        return;
			aStack.pop(element);
		    pointer = element.pointer;
		}
		//���������������������
		if(Left == element.tag){
			element.tag = Right;
			aStack.push(element);
			if(In == order) //�����ڴ˷��ʽڵ�
				Visit(pointer->data);
			pointer = pointer->right;
		}
	}
}

////////////////////////////////////////////////////////////
/*�ǵݹ�ǰ�����ζ�����
* 1. ����һ���ڵ㣬���ʸýڵ㣬���Ƴ�ջ��;
* 2. �½�������������;
* 3. һֱ���ε�Ҷ�ӽڵ㣬��ջ�������ڵ�;
* 4. ��������������ָʾ���θýڵ��������;
*/
template<typename T>
inline void CBTree<T>::PreOrderTraverseWithoutRecursion( 
	const CBTNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	CStack<CBTNode<T>* > aStack;
	CBTNode<T>* pointer = const_cast<CBTNode<T>* >(root);
	
	//// �̳���ľ���ʵ�ְ汾��
	//while(!aStack.IsEmpty() || pointer)
	//{
	//	if(pointer)
	//	{
	//		Visit(pointer->data);
	//		aStack.push(pointer);
	//		pointer = pointer->left;
	//	}else{//˵������Ҷ�ӽڵ����һ���ڵ�
	//		aStack.pop(pointer);//���ݵ���һ���ڵ�
	//		pointer = pointer->right;
	//	}
	//}
	//���ǣ�ǰ�򻹿����ٽ����Ż�
	//����˼���ǣ�����ջ�д洢���ǽ�����Ҫ���ʵĽڵ㣬��ô
	//�Ѿ����ʵĽڵ�û�б�Ҫ����ջ�У�����ջ�д洢��Ԫ�غͼ�����ջ��ջ�Ĳ���
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

/*�ǵݹ��������ζ�����
* 1. ����һ���ڵ㣬�Ƴ�ջ�У�
* 2. ��������������
* 3. ������������������ջ��Ԫ�أ�����֮;
* 4. ������������
*/
template<typename T>
inline void CBTree<T>::InOrderTraverseWithoutRecursion( 
	const CBTNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	CStack<CBTNode<T>* > aStack;
	CBTNode<T>* pointer = const_cast<CBTNode<T>* >(root);

	//�������Լ�ʵ�ֵİ汾
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
	//�̿��龭��ʵ�ְ汾��ǧ������
	//while(true)//����������
	//{
	//	while(NULL != pointer)
	//	{
	//		element.pointer = pointer;
	//		element.tag = Left;
	//		aStack.push(element);
	//		pointer = pointer->left;//����������������������
	//	}
	//    aStack.pop(element);
	//	pointer = element.pointer;
	//	//������������
	//	while(Right == element.tag)
	//	{
	//		Visit(pointer->data);
	//		if(aStack.IsEmpty())
	//	        return;
	//        aStack.pop(element);
 //           pointer = element.pointer;
	//	}
 //       //������������
 //       element.tag = Right;
 //       aStack.push(element);
 //       pointer = pointer->right;
	//}

	//�Լ�������ʵ�ְ汾��
	//�㷨���ǲ�����Լ���󲻶��Ż�����Ȼ����ԭ���̿����ϵİ汾
	while(true){
		//�ʼ����������
		while(pointer){
			element.pointer = pointer;
			element.tag = Left;
			aStack.push(element);
			pointer = pointer->left;
		}
		//������������ϣ�ջ��Ԫ�ص�ջ
		aStack.pop(element);
		pointer = element.pointer;
		//��ʱ���ʼԪ��ΪLeft����
		while(element.tag == Right){
			Visit(pointer->data);
			if(aStack.IsEmpty())//ֱ��ջΪ��
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