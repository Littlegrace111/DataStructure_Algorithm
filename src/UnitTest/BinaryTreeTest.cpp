#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "..\Tree\BinaryTree.h"
#include "..\Tree\BTreeTraverse.h"

using namespace std;

int main(int argc, char* argv[])
{
	
	BTreeNode<char> a('a');
	BTreeNode<char> b('b');
	BTreeNode<char> c('c');
	BTreeNode<char> d('d');
	BTreeNode<char> e('e');
	BTreeNode<char> f('f');
	BTreeNode<char> g('g');
	BTreeNode<char> h('h');
    BTreeNode<char> i('i');
	BTreeNode<char> j('j');

	//构造测试二叉树
	//     a
	//    / \
	//   b   c
	//  / \   \
	// d  e    f
	//   / \  / \
	//  j  g h   i
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.right = &e;
	c.right = &f;
	e.left = &j;
	e.right = &g;
	f.left = &h;
	f.right = &i;

	//BinaryTree<char> bTree(&a);
	BinaryTree<char>* pbTree = new BinaryTree<char>(&a);

	cout<<b.data<<" parent: "<<(pbTree->Parent(&b))->data<<endl;
	cout<<c.data<<" parent: "<<(pbTree->Parent(&c))->data<<endl;
	cout<<"nodes counting: "<<pbTree->GetNodesCount()<<endl;
	cout<<"leaf counting: "<<pbTree->GetLeafCount()<<endl;
	cout<<"the depth of node "<<b.data<<" is "<<pbTree->GetDepth(&b)<<endl;
	cout<<"right sibling of "<<j.data<<" is "<<(pbTree->RightSibling(&j))->data<<endl;
	cout<<"left sibling of "<<i.data<<" is "<<(pbTree->LeftSibling(&i))->data<<endl;

	//递归遍历
	BTreeTraverse<char> traverse;

	cout<<"PreOrder: "<<endl;
	traverse.PreOrderTraverse(*pbTree, PrintElement);
	cout<<endl<<"InOrder: "<<endl;
	traverse.InOrderTraverse(*pbTree, PrintElement);
	cout<<endl<<"PostOrder: "<<endl;
	traverse.PostOrderTraverse(*pbTree, PrintElement);

	//非递归遍历
	cout<<endl<<"PreOrder without recursion: "<<endl;
	traverse.PreOrderTraverseWithoutRecursion(*pbTree, PrintElement);
	cout<<endl<<"InOrder without recursion: "<<endl;
	traverse.InOrderTraverseWithoutRecursion(*pbTree, PrintElement);
	cout<<endl<<"PostOrder without recursion: "<<endl;
	traverse.PostOrderTraverseWithoutRecursion(*pbTree, PrintElement);

	cout<<endl<<"广度优先遍历："<<endl;
	traverse.LevelOrderTraverse(*pbTree, PrintElement);
	cout<<endl;

	system("pause");
	return 0;
}