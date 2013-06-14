/*******************************************************************
//main.cpp : Defines the entry point for the console application.
//version  : 1.0
//Author   : Grace
//Date     : 2012-11-15 10:15
*******************************************************************/

#include <stdio.h>
#include <iostream>
#include "Single_Linker.h"

using namespace std;

int main(int argc, char* argv[])
{
	int nCount;
	CSList<int> slist;

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	slist.InsertAfter(slist.InsertAfter(slist.AddHead(1), 2), 3);
	slist.InsertAfter(slist.InsertAfter(slist.GetCount(), 4), 5);
	slist.InsertAfter(slist.GetCount(), 6);
	slist.AddTail(10);
	slist.InsertAfter(slist.InsertBefore(slist.GetCount(), 7), 8);
	slist.SetAt(slist.GetCount(), 9);

	//print out elements
	nCount = slist.GetCount();
	for(int i=0; i<nCount; ++i)
		cout<<slist.GetAt(i+1);
	cout<<endl;

	slist.RemoveHead();
	slist.RemoveTail();

	nCount = slist.GetCount();
	for(int i=0; i<nCount; ++i)
		cout<<slist.GetAt(i+1);
	cout<<endl;

	getchar();
	return 0;
}

