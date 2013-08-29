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
		//�����¼i����С��
		int Smallest = i;
		//��ʼ���ɨ������ʣ���¼
		for(int j=i+1; j<n; j++)
			//������ָ�С�ļ�¼����¼����λ��
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