#ifndef _BTREE_TRAVERSE_H
#define _BTREE_TRAVERSE_H
#include "..\LinkerList\Queue.h"
#include "..\LinkerList\Stack.h"
#include "BinaryTree.h"

//decalaration
template<class T> class BinaryTree;

//Visit�ص�����
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
	//���ڶ��������ε�ͨ�ÿ�ܣ�ͳһ֧��ǰ�����򣬺���
	enum Order{Pre, In, Post};
	//�ݹ����ε�ͨ�ÿ��
	void Traverse(
		const Order order,
		const BTreeNode<T> *p,
		void (*Visit)(const T &data)
		)const;

	//�ǵݹ�汾
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

	//�ǵݹ����ε�ͨ�ÿ��
	/*Trace��ʶλ��
	* Left: ��ʶ�˽ڵ��Ѿ���������������;
	* Right: ��ʶ�˽ڵ��Ѿ�����������������������;*/
	enum Tags{Left, Right};
	/*����ջ�е����ݣ�pointer��tags*/
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

	//�����������
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

	//������ȱ���
	void LevelOrderTraverse(BinaryTree<T> &tree, void (*Visit)(const T &data))
	{
		LevelOrderTraverse(tree.root, Visit);
	}
};

//����������Σ�
//���ڵ���ӣ�
//���в�Ϊ�գ����ʶ��ף����׳��ӣ�����������������ӣ�
//��������Ĳ���ֱ��Ϊ�գ�
template<class T>
inline void BTreeTraverse<T>::LevelOrderTraverse(
	const BTreeNode<T>* p,
	void (*Visit)(const T &data))const
{
	CQueue<BTreeNode<T>*> aQueue;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>*>(p);
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
template<class T>
inline void BTreeTraverse<T>::Traverse(
	const Order order,
	const BTreeNode<T>* p,
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
template<class T>
inline void BTreeTraverse<T>::TraverseWithoutRecursion(
	const Order order,
	const BTreeNode<T>* root,
	void (*Visit)(const T &data) )const
{
	StackElement<T> element;
	CStack<StackElement<T> > aStack;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>*>(root);
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
template<class T>
inline void BTreeTraverse<T>::PreOrderTraverseWithoutRecursion( 
	const BTreeNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	CStack<BTreeNode<T>* > aStack;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>* >(root);

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
template<class T>
inline void BTreeTraverse<T>::InOrderTraverseWithoutRecursion( 
	const BTreeNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	CStack<BTreeNode<T>* > aStack;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>* >(root);

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

template<class T>
inline void BTreeTraverse<T>::PostOrderTraverseWithoutRecursion( 
	const BTreeNode<T> *root, 
	void (*Visit)(const T &data) ) const
{
	StackElement<T> element;
	CStack<StackElement<T> > aStack;
	BTreeNode<T>* pointer = const_cast<BTreeNode<T>*>(root);

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

#endif