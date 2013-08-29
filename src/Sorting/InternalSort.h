#ifndef _INTERNAL_SORTING_H
#define _INTERNAL_SORTING_H
#include <iostream>

template<class Record, class Compare>
class Sorter{
protected:
	//交换数组中的两个元素
	static void swap(Record Array[], int i, int j);
public:
	//对数组Array进行排序
	void Sort(Record Array[], int n);
	//输出数组内容
	void PrintArray(Record array[], int n);
};

template<class Record, class Compare>
void Sorter<Record, Compare>::PrintArray( Record array[], int n )
{
	//输出数组内容
	for(int i=0; i<n; i++)
		std::cout<<array[i]<<" ";
	std::cout<<endl;
}

template<class Record, class Compare>
void Sorter<Record, Compare>::swap( Record Array[], int i, int j )
{
	//交换数组中的两个元素
	Record TempRecord = Array[i];
	Array[i] = Array[j];
	Array[j] = TempRecord;
}

class int_intCompare{
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

template <class Record, class Compare>
class InsertSorter: public Sorter<Record, Compare>{};

//直接插入排序类
template <class Record, class Compare>
class StraightInsertSorter: public InsertSorter<Record, Compare>{
public:
	void Sort(Record Array[], int n);
};

//直接插入排序
//逐个处理待排序的记录，每个新记录都要与前面那些已排好序的记录进行比较，然后插入到适当的位置。
//稳定
//空间代价：O(1)
//时间代价：
//  最佳情况：n-1次比较，0次比较；
//  最差情况：比较和交换次数为O(n^2);
template <class Record, class Compare>
void StraightInsertSorter<Record, Compare>::Sort( Record Array[], int n )
{//Array[]为待排序数组， n为数组长度
	for(int i=1; i<n; i++){//依次插入第i录
		for(int j=i; j>0; j--){
			if(Compare::lt(Array[j], Array[j-1]))
				swap(Array, j, j-1);
			else break;
		}
	}
}

//优化的插入排序类
template<class Record, class Compare>
class ImprovedInsertSorter: public InsertSorter<Record, Compare>
{
public:
	void Sort(Record Array[], int n);
};

//优化的插入排序算法
template<class Record, class Compare>
void ImprovedInsertSorter<Record, Compare>::Sort( Record Array[], int n )
{
	Record TempRecord;  //临时变量
	for(int i=1; i<n; i++){
		TempRecord = Array[i];
		//从i开始往前寻找记录i的正确位置
		int j = i-1;
		//将那些大于等于记录i的记录后移
		while((j>=0)&&(Compare::lt(TempRecord, Array[j])))
		{
			Array[j+1] = Array[j];
			j--;
		}
		//此时j后面就是记录i的正确位置，回填
		Array[j+1] = TempRecord;
	}
}


//二分法插入排序
//在插入第i个记录时，前面的记录已经是有序的，
//可以用二分法查找第i个记录的正确位置。
template <class Record, class Compare>
class BinaryInsertSorter: public InsertSorter<Record, Compare>
{
public:
	void Sort(Record Array[], int n);
};

//算法分析：
//稳定
//空间代价：O(1)
//时间代价：
//   插入每个记录需要O(log i)次比较
//   最多移动i+1次，最少2次（移动临时记录）
//   因此最佳情况下总时间代价为O(nlogn)
//   最差和平均情况下仍为O(n^2)
template <class Record, class Compare>
void BinaryInsertSorter<Record, Compare>::Sort( Record Array[], int n )
{
	//Array[] 为待排序数组，n为数组长度
	Record TempRecord; 
	//记录已经排好序序列的左，右，中位置
	int left, right, middle;
	//依次插入第i个记录
	for(int i=1; i<n; i++)
	{
		//保存当前待插入的记录
		TempRecord = Array[i];
		//记录已排好序序列的左右位置
		left = 0; right = i-1;
		//开始查找待插入记录的正确位置
		while(left <= right){
			//中间位置
			middle = (left + right)/2;
			//如果待插入记录比中间记录小，就在左一半中查找；
			//否则就在右一半中查找
			if(Compare::lt(TempRecord, Array[middle]))
				right = middle -1;
			else 
				left = middle -1;
		}
		//将前面所有大于当前待插入记录的记录后移
		for(int j=i-1; j>=left; j--)
			Array[j+1] = Array[j];
		//将待插入记录回填到正确的位置
		Array[left] = TempRecord;
	}
}

//冒泡排序
//不停比较相邻的记录，如果不满足排序要求，就交换相邻记录，知道所有的记录都已经排好序
template <class Record, class Compare>
class BubbleSorter: public Sorter<Record, Compare>
{//冒泡排序类
public:
	void Sort(Record Array[], int n);
};

//稳定
//空间代价： O(1)
//时间代价：O(n^2)
template <class Record, class Compare>
void BubbleSorter<Record, Compare>::Sort( Record Array[], int n )
{
	//第i个记录冒泡
	for(int i=1; i<n; i++)//依次比较相邻记录，如果发现逆置，就交换
		for(int j=n-1; j>=i; j--)
			if(Compare::lt(Array[j], Array[j-1]))
				swap(Array, j, j-1);
}

//优化的冒泡排序
//改进：检查每次冒泡过程中是否发生过交换，如果没有，则表明整个数组已经排好序了，排序结束
//避免不必要的比较
template <class Record, class Compare>
class ImporvedBubbleSorter: public Sorter<Record, Compare>
{
public:
	void Sort(Record, Array[], int n);
};

template <class Record, class Compare>
void ImporvedBubbleSorter<Record, Compare>::Sort( Record, Array[], int n )
{
	bool NoSwap; // 是否发生交换的标志
	for(int i=1; i<n; i++)
	{
		NoSwap = true;
		for(int j=n-1; j>=i; j--)
			if(Compare::lt(Array[j], Array[j-1]))
			{
				swap(Array, j, j-1);
				NoSwap = false;//如果发生了交换，标志变为假
			}
		//如果没有发生交换，表示已排好序，结束算法
		if(NoSwap)
			return;
	}
}

//直接选择排序
//找出剩下的未排序记录中的最小记录，然后直接与数组中第i个记录交换，
//比冒泡排序减少了移动次数
template <class Record, class Compare>
class StraightSelectSorter: public Sorter<Record, Compare>
{
public:
	void Sort(Record Array[], int n);
};

//不稳定
//空间代价：O(1)
//时间代价：O（n^2）
template<class Record, class Compare>
class StraightSelectSorter: public Sorter<Record, Compare>
{
	//依次选出第i小的记录，即剩余记录中最小的那个
	for(int i=0; i<n-1; i++)
	{
		//首先架设记录i就是最小的
		int Smallest = i;
		//开始向后扫描所有剩余记录
		for(int j=i+1; j<n; j++)
			if(Compare::lt(Array[j], Array[Smallest]))
				Smallest = j;
		//将第i小的记录放在数组中第i个位置
		swap(Array, i, Smallest);
	}
};
#endif 