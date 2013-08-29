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

//�ǵݹ���㷨���
//�ڶ��������������ڵ�Ϊ�������ұߵĽڵ�
template<typename T>
inline BTreeNode<T>* BSearchTree<T>::FindMax( BTreeNode<T>* p )
{
	while(p->right)
		p = p->right;
	return p;
}

//�ݹ���㷨���
//ͬ����������������ߵĽڵ�Ϊ������С�ڵ�
template<typename T>
inline BTreeNode<T>* BSearchTree<T>::FindMin( BTreeNode<T>* p )
{
	if(NULL == p->left)
		return p;
	else 
		return FindMin(p->left);
}

//�����������ĵݹ�ɾ�����:
//1. �½����β���Ҫɾ���Ľ��p��
//2. ���������Ҷ��������ɾ����
//   �������һ����Ҷ�����丸�������ƹ��ý��ָ������ӽ�㣬Ȼ��ý�㱻ɾ����
//   ��������������Թ�Ϊһ�ࣻ
//3. �����������ӵĽ�㣺
//   ɾ������һ��������������С��㣨Ҳ��������ݹ�ĵ�һ����㣩����ý������ݲ��ݹ�ɾ���Ǹ����;
//             ��Ϊ�������е���С��㲻����������ӣ����Եڶ���ɾ������˻�����һ�������
//   ɾ�����Զ���ͬ����������������㣨Ҳ��������ݹ�����һ����㣩����ý������ݲ��ݹ�ɾ���Ǹ���㣻
//   ��ɾ���㷨��ƽ�������Եõ��Ľ�
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

//�����������ķǵݹ�汾
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
inline BTreeNode<T>* BSearchTree<T>::InsertNode( 
	const T &data, BTreeNode<T>* p )
{
	if(root == NULL){//if an empty tree, create root node  and return
		root = CreateNewNode(data);
		return root;
	}

	if(NULL == p){
		p = CreateNewNode(data);
	}else if(data < p->data) {//������
		//MYTRACE("go to left child tree");
		p->left = InsertNode(data, p->left);
	}else if(data > p->data) {//������
		//MYTRACE("go to right child tree");
		p->right = InsertNode(data, p->right);
	}
	return p;
}

#endif