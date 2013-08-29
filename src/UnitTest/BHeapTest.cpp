#include <stdio.h>
//#include <iostream>
#include "..\Tree\Heap.h"

using namespace std;

int main()
{
	MinHeap<int> bHeap(100);
	bHeap.Insert(6);
	bHeap.Insert(5);
	bHeap.Insert(4);
	bHeap.Insert(7);
	bHeap.Insert(9);
	bHeap.Insert(8);
	bHeap.Insert(0);
    bHeap.Insert(2);
	bHeap.Insert(11);
	bHeap.Insert(10);
	bHeap.Insert(23);
	bHeap.Insert(17);

	//bHeap.debug_preview();

	int iValue = 0;
	bHeap.Remove(iValue);
	
	cout<<iValue<<endl;
	//bHeap.debug_preview();
	system("pause");
	return 0;
}