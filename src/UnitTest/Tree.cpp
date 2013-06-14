// Tree.cpp : Defines the entry point for the console application.
#include <iostream>
#include <string>
#include "..\Tree\BTree.h"
#include "..\Tree\BSTree.h"

using namespace std;

//Visit回调函数
template<typename T>
static void PrintElement(const T &data)
{
	cout<<data;
}

static void BinaryTreeTest()
{
	char testcase[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', '\0'};
	cout<<"Create a binary tree: "<<testcase<<endl;
	CBTree<char> BinaryTree(testcase, 7);

	cout<<"深度优先遍历:"<<endl;
	//递归遍历
	cout<<"PreOrder: "<<endl;
	BinaryTree.PreOrderTraverse(PrintElement);
	cout<<endl<<"InOrder: "<<endl;
	BinaryTree.InOrderTraverse(PrintElement);
	cout<<endl<<"PostOrder: "<<endl;
	BinaryTree.PostOrderTraverse(PrintElement);

	//非递归遍历
	cout<<endl<<"PreOrder without recursion: "<<endl;
	BinaryTree.PreOrderTraverseWithoutRecursion(PrintElement);
	cout<<endl<<"InOrder without recursion: "<<endl;
	BinaryTree.InOrderTraverseWithoutRecursion(PrintElement);
	cout<<endl<<"PostOrder without recursion: "<<endl;
	BinaryTree.PostOrderTraverseWithoutRecursion(PrintElement);

	cout<<endl<<"广度优先遍历："<<endl;
	BinaryTree.LevelOrderTraverse(PrintElement);

	cout<<endl<<"二叉树节点数："<<BinaryTree.GetNodesCount()<<endl;
	cout<<"二叉树叶子节点数："<<BinaryTree.GetLeafCount()<<endl;
	cout<<"二叉树深度："<<BinaryTree.GetDepth()<<endl;
}

static void BinarySearchTreeTest()
{
	int testcase[] = {2};
	CBSTree<int> BSTree;
	
	BSTree.InsertNode(5);
	for(int i=0; i<10; i++)
		BSTree.InsertNode(i);

	cout<<endl<<"InOrder: "<<endl;
	BSTree.InOrderTraverse(PrintElement);
}

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	BinaryTreeTest();
	BinarySearchTreeTest();
	//退出
	char temp;
	cin>>temp;
	return 0;
}

