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
	enum Sibling{Left, Right}; // ��ʶ�������ֵܻ������ֵ�

	bool isEmpty() const; // �ж϶������Ƿ�Ϊ��
	BTreeNode<T>* GetParent(BTreeNode<T>* root, const BTreeNode<T>* current)const;
	void DeleteTree(BTreeNode<T>* root);	
	BTreeNode<T>* GetSibling( const Sibling sib, const BTreeNode<T>* current) const;
	void GetNodesCount(const BTreeNode<T>* current, unsigned int* ulCount) const;
	void GetLeafCount(const BTreeNode<T>* current, unsigned int* ulCount) const;
public:
	unsigned int GetDepth(const BTreeNode<T>* current) const;//��ö����������
	unsigned int GetNodesCount()const;//��ö������ڵ����
	unsigned int GetLeafCount() const;//���Ҷ�ӽڵ����
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
		if((current->left == NULL) && (current->right == NULL))//Ҷ�ӽ��
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
	else if ((NULL == current->left) && (NULL == current->right))//Ҷ�ӽ��
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
	//�Ժ������εķ�ʽɾ����������������
	if(p){
		DeleteTree(p->left); //�ݹ�ɾ��������
		DeleteTree(p->right); //�ݹ�ɾ��������
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

	//����current���ĸ����
	BTreeNode<T>* temp = Parent(current);
	//��������Ϊ��:Ϊ�����
	if(temp==NULL)
		return NULL;
	else if(sib == Left && temp->left != current)//��ȡ���ֵ�
		return temp->left;
	else if(sib == Right && temp->right != current )//��ȡ���ֵ�
		return temp->right;
	else
		return NULL;
}

template<class T>
BTreeNode<T>* BinaryTree<T>::RightSibling( 
	const BTreeNode<T>* current ) const
{   
	//���current��Ϊ��
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
	//����current���ĸ����ָ��
	if(current == NULL || current == root)
		return NULL; // �ս�����currentΪ�������û�и����
	//���õݹ麯��Ѱ�Ҹ����
	return GetParent(root, current);
}

template<class T>
BTreeNode<T>* BinaryTree<T>::GetParent( 
	BTreeNode<T>* root, 
	const BTreeNode<T>* current ) const
{
	//�Ӷ�������root��㿪ʼ������current���
	BTreeNode<T>* temp; // �����
	if(root == NULL) //defensive coding
		return NULL;

	//��������Ϊ�����
	if(root->left == current || root->right == current)
		return root;
	//�ݹ�Ѱ�Ҹ����
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