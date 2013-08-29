// Tree.cpp : Defines the entry point for the console application.
#include <iostream>
#include <string>
#include "..\Tree\BinaryTree.h"
#include "..\Tree\AVLTree.h"
#include "..\Tree\BTreeTraverse.h"

using namespace std;


int main(int argc, char* argv[])
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	BinaryTree<int>* pSearchTree = new BSearchTree<int>;

	pSearchTree->Insert(1);
	pSearchTree->Insert(2);
	pSearchTree->Insert(3);
	pSearchTree->Insert(4);
	pSearchTree->Insert(5);
	pSearchTree->Insert(6);
	pSearchTree->Insert(7);

	BTreeTraverse<int> Traverse;
	cout<<"Search Tree level order traverse:"<<endl;
	Traverse.LevelOrderTraverse(*pSearchTree, PrintElement);

	BinaryTree<int>* pAvlTree = new CAVLTree<int>;

	pAvlTree->Insert(1);
	pAvlTree->Insert(2);
	pAvlTree->Insert(3);
	pAvlTree->Insert(4);
	pAvlTree->Insert(5);
	pAvlTree->Insert(6);
	pAvlTree->Insert(7);

	cout<<"AVLTree level order tree: "<<endl;
	Traverse.LevelOrderTraverse(*pAvlTree, PrintElement);

	system("pause");
	return 0;
}

