#ifndef _SORTING_H
#define _SORTING_H

#include <iostream>

class Compare{
public:
	static bool lt(int x, int y)
	{
		return x<y;
	}

	static bool eq(int x, int y)
	{
		return x==y;
	}

	static bool gt(int x, int y)
	{
		return x>y;
	}
};

template<class Record, class Compare>
class Sorter//总排序类
{
protected:
	//交换数组中的两个元素
	static void swap(Record Array[], int i, int j);
public:
	//对数组Array进行排序
	void Sort(Record Array[], int n);
    //输出数组内容
	void PrintArray(Record Array[], int n);
};

template<class Record, class Compare>
void Sorter<Record, Compare>::PrintArray( Record Array[], int n )
{
	for(int i=0; i<n; i++)
		cout<<Array[i]<<" ";
	cout<<endl;
}

template<class Record, class Compare>
void Sorter<Record, Compare>::swap( Record Array[], int i, int j )
{
	Record TempRecord = Array[i];
	Array[i] = Array[j];
	Array[j] = TempRecord;
}




#endif