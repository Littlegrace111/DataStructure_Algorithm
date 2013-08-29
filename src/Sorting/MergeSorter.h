#ifndef _MERGESORTER_H
#define _MERGESORTER_H

#include "Sorter.h"

template <class Record, class Compare>
class TwoWayMergeSorter: public Sorter<Record, Compare>
{
private:
	void Merge(Record Array[], Record TempArray[], int left, int right, int middle);
public:
	void MergeSort(Record Array[], Record TempArray[], int left, int right);
};

//归并函数
template <class Record, class Compare>
void TwoWayMergeSorter<Record, Compare>::Merge( Record Array[], Record TempArray[], int left, int right, int middle )
{
	//将数组暂存入临时数组
	for(int j=left; j<=right; j++)
		TempArray[j] = Array[j];
	int index1 = left; //左边子序列的起始位置
	int index2 = middle+1; //右子序列起始位置
	int i = left;    //从左开始归并
	while(index1 <= middle && index2 <= right)
	{
		//取较小者插入合并数组中
		if(Compare::lt(TempArray[index1], TempArray[index2]))
			Array[i++] = TempArray[index1++];
		else
			Array[i++] = TempArray[index2++];
	}
	//处理剩余记录
	while(index1 <= middle)
		Array[i++] = TempArray[index1++];
	while(index2<= right)
		Array[i++] = TempArray[index2++];
}

template <class Record, class Compare>
void TwoWayMergeSorter<Record, Compare>::MergeSort( Record Array[], Record TempArray[], int left, int right )
{
	//如果序列中只有0或1个记录
	if(left < right)
	{
		//从中间划分为两个子序列
		int middle = (left+right)/2;
		//对左边一半进行递归
		MergeSort(Array, TempArray, left, middle);
		//对右边一半进行递归
		MergeSort(Array, TempArray, middle+1, right);
		//进行归并
		Merge(Array, TempArray, left, right, middle);
	}
}

//优化的归并排序
#define THRESHOLD_MERGE 16

template <class Record, class Compare>
class ImprovedTwoWayMergeSorter: public TwoWayMergeSorter<Record, Compare>
{
private:
	void Merge(Record Array[], Record TempArray[], int left, int right, int middle);
	void DoSort(Record Array[], Record TempArray[], int left, int right);
public:
	void MergeSort(Record Array[], Record TempArray[], int left, int right);
};

template <class Record, class Compare>
void ImprovedTwoWayMergeSorter<Record, Compare>::Merge( Record Array[], Record TempArray[], int left, int right, int middle )
{
	int index1, index2;
	int i,j,k;
	for(i=left; i<=middle; i++)//复制左边的子序列
		TempArray[i] = Array[i];
	//复制右边的子序列，但顺序颠倒过来
	for(j=1; j<=right-middle; j++)
		TempArray[right-j+1] = Array[j+middle];
	//开始归并
	for(index1=left, index2=right, k=left; k<=right; k++)
		if(Compare::lt(TempArray[index1], TempArray[index2]))
			Array[k] = TempArray[index1++];
		else 
			Array[k] = TempArray[index2++];
}

template <class Record, class Compare>
void ImprovedTwoWayMergeSorter<Record, Compare>::MergeSort( Record Array[], Record TempArray[], int left, int right )
{
	if(right <= left)
		return;
	//如果序列长度大于阈值（16最佳），跳出递归
	if(right-left+1 > THRESHOLD_MERGE)
	{
		int middle = (left + right)/2; //从中间划分
		DoSort(Array, TempArray, left, middle);
		DoSort(Array, TempArray, middle+1, right);
		Merge(Array, TempArray, left, right, middle);
	}
}

template <class Record, class Compare>
void ImprovedTwoWayMergeSorter<Record, Compare>::MergeSort( Record Array[], Record TempArray[], int left, int right )
{
	DoSort(Array, TempArray, left, right);
	//最后对整个序列进行依次直接插入排序
	ImprovedInsertSorter<Record, Compare> insert_sorter;
	insert_sorter.ImprovedInsertSort(&Array[left], right-left+1);
}

#endif