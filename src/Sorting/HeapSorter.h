#ifndef _HEAPSORTER_H
#define _HEAPSORTER_H

#include "Sorter.h"

template <class Record, class Compare>
class StraightSelectSorter:public Sorter<Record, Compare>
{
public:
	void SelectSort(Record Array[], int n);
};

template <class Record, class Compare>
void StraightSelectSorter<Record, Compare>::SelectSort( Record Array[], int n )
{
	for(int i=0; i<n-1; i++)
	{
		//假设记录i是最小的
		int Smallest = i;
		//开始向后扫描所有剩余记录
		for(int j=i+1; j<n; j++)
			//如果发现更小的记录，记录它的位置
			if(Compare::lt(Array[j], Array[Smallest]))
				Smallest = j;
		swap(Array, i, Smallest);
	}
}

template <class Record, class Compare>
class HeapSorter: public Sorter<Record, Compare>
{
public:
	void HeapSort(Record Array[], int n);
};

#endif