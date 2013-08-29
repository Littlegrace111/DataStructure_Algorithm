#ifndef _INSERTSORTER_H
#define _INSERTSORTER_H

#include "Sorter.h"

template <class Record, class Compare>
class InsertSorter: public Sorter<Record, Compare>
{

};

template <class Record, class Compare>
class StraightInsertSorter: public InsertSorter<Record, Compare>
{//直接插入排序类
public:
	void StraightInsertSort(Record Array[], int n);
};

template <class Record, class Compare>
void StraightInsertSorter<Record, Compare>::StraightInsertSort( Record Array[], int n )
{
	for(int i=1; i<n; i++)
	{//依次与前面的记录进行比较，发现逆置就交换
		for(int j=i; j>0; j--){
			if(Compare::lt(Array[j], Array[j-1]))
				swap(Array, j, j-1);
			else
				break; //此时i前面记录已排好
		}	
	}
}

template <class Record, class Compare>
class ImprovedInsertSorter: public InsertSorter<Record, Compare>
{
public:
	void ImprovedInsertSort(Record Array[], int n);
};

template <class Record, class Compare>
void ImprovedInsertSorter<Record, Compare>::ImprovedInsertSort( Record Array[], int n )
{
	Record TempRecord;
	for(int i=1; i<n; i++){
		TempRecord = Array[i];
		//从i开始往前寻找记录i的正确位置
		int j = i-1;
		//将那些大于等于记录i的记录后移
		while((j>=0)&&(Compare::lt(TempRecord, Array[j])))
		{
			Array[j+1] = Array[j];
			j = j-1;
		}
		//此时j后面就是记录i的正确位置，回填
		Array[j+1] = TempRecord;
	}
}

template <class Record, class Compare>
class BinaryInsertSorter: public InsertSorter<Record, Compare>
{
public:
	void BinaryInsertSort(Record Array[], int n);
};

template <class Record, class Compare>
void BinaryInsertSorter<Record, Compare>::BinaryInsertSort( Record Array[], int n )
{
	Record TempRecord;
	//记录已排好序序列的左、右、中的位置
	int left, right, middle;
	//依次插入第i个记录
	for(int i=1; i<n; i++){
		//保存当前待插入记录
		TempRecord = Array[i];
		left = 0;
		right = i-1;
		//开始查找待插入记录的正确位置
		while(left <= right){
			middle = (left + middle)/2;
			//如果待插入记录比中间记录小，就在左一半中查找，否则在右一半中查找
			if(Compare::lt(TempRecord, Array[middle]))
				right = middle-1;
			else
				left = middle+1;
		}
		//将前面所有大于当前待插入记录的记录后移
		for(int j=i-1; j>=left; j--)
			Array[j+1] = Array[j];
		//将待插入记录回填到正确位置
		Array[left] = TempRecord;
	}
}

#endif