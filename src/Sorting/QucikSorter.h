#ifndef _QUICKSORTER_H
#define _QUICKSORTER_H

#include "Sorter.h"
#include "InsertSorter.h"

template<class Record, class Compare>
class QuickSorter:public Sorter<Record, Compare>
{
protected:
	int SelectPivot(int left, int right);//选择轴值，返回轴值下标
	int Partition(Record Array[], int left, int right);
public:
	void QuickSort(Record Array[], int left, int right);
};

template<class Record, class Compare>
int QuickSorter<Record, Compare>::Partition( Record Array[], int left, int right )
{//分割函数，分割后轴值已到达正确位置
	Record TempRecord; //存放轴值的临时变量
	int i = left;
	int j = right;
	//将轴值放入临时变量
	TempRecord = Array[j];
	//开始分割，i，j不断向中间移动，直到相遇
	while(i != j){
		//i指针右移，直到找到一个大于等于轴值的记录
		while(Compare::lt(Array[i], TempRecord)&&(j>i))
			i++;
		//如果i，j未相遇就将逆序元素换到右边空闲的位置
		if(i<j){
			Array[j] = Array[i];
			j--; //j指针左移一步
		}
		//j指针左移，直到找到一个小于等于轴值的记录
		while(Compare::gt(Array[j], TempRecord)&&(j>i))
			j--;
		//如果i，j未相遇就将逆序元素换到左边空闲位置
		if(i<j){
			Array[i] = Array[j];
			i++; //i指针向右移一步
		}
	}
	//把轴值回填到分界位置i上
	Array[i] = TempRecord;
	return i;
}

template<class Record, class Compare>
int QuickSorter<Record, Compare>::SelectPivot( int left, int right )
{
	//三数中值法
	return (left + right)/2;
}

template<class Record, class Compare>
void QuickSorter<Record, Compare>::QuickSort( Record Array[], int left, int right )
{//Array[]为待排序数组，i和j分别为数组两端
	//如果子序列中只有0或1个记录，就不需要排序
	if(right <= left)
		return;
	//选择轴值
	int pivot = SelectPivot(left, right);
	//分割前先将轴值放到数组末端
	swap(Array, pivot, right);
	//对剩余的记录进行分割
	pivot = Partition(Array, left, right);
	//对轴值左边的子序列进行递归快速排序
	QuickSort(Array, left, pivot-1);
	//对轴值右边的子序列进行递归快速排序
	QuickSort(Array, pivot+1, right);
}


//优化的快速排序
#define THRESHOLD 16

template<class Record, class Compare>
class ImprovedQuickSorter: public QuickSorter<Record, Compare>
{
private:
	//选择轴值，返回轴值下标
	//int SelectPivot(int left, int right);
	//分割，返回轴值位置
	//int Partition(Record Array[], int left, int right);
	void DoSort(Record Array[], int left, int right);
public:
	void QuickSort(Record Array[], int left, int right);
};

template<class Record, class Compare>
void ImprovedQuickSorter<Record, Compare>::DoSort( Record Array[], int left, int right )
{
	//如果序列中只有0或1个记录，就不用排序
	if(right <= left)
		return;
	//如果序列长度小于等于阈值（16最佳），停止分割跳出递归
	if(right=left+1 > THRESHOLD)
	{
		//选择轴值
		int pivot = SelectPivot(left, right);
		//将轴值放在数组末端
		swap(Array, pivot, right);
		//对剩余的记录进行分割
		pivot = Partition(Array, left, right);
		//对分割出的子序列进行递归快速排序
		//对轴值左右分别进行排序
		DoSort(Array, left, pivot-1);
		DoSort(Array,pivot+1, right);
	}
}

template<class Record, class Compare>
void ImprovedQuickSorter<Record, Compare>::QuickSort( Record Array[], int left, int right )
{   //优化的快速排序，Array[]为待排序数组，i，j分别为数组两端
	//先对序列进行递归排序
	DoSort(Array, left, right);
	//最后对整个序列进行一次直接插入排序
	ImprovedInsertSorter<Record, Compare> insert_sort;
	insert_sort.ImprovedInsertSort(Array, right-left+1);
}

#endif