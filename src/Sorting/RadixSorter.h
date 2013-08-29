#ifndef _RADIXSORTER_H
#define _RADIXSORTER_H

#include <iostream>
#include "Sorter.h"

template <class Record>
class BucketSorter: public Sorter<Record, Compare>
{
public:
	void BucketSort(Record Array[], int n, int max);
};

template <class Record>
void BucketSorter<Record>::BucketSort( Record Array[], int n, int max )
{//桶式排序，Array[]为待排序数组，所有记录都位于区间[0, max)上
	int* TempArray = new Record[n]; // 临时数组
	int* count = new int[max]; //小于等于i的元素个数
	int i;
	//复制数组到临时数组
	for(i=0; i<n; i++)
		TempArray[i] = Array[i];
	//所有计数器初始都为0
	for(i=0; i<max; i++)
		count[i] = 0;
	//统计每个取值出现的次数
	for(i=0; i<n; i++)
		count[Array[i]]++;
	//统计小于等于i的元素个数
	for(i=1; i<max; i++)
		count[i] = count[i-1]+count[i];
	//按顺序输出有序序列
	for(i=n-1; i>=0; i--)
		Array[--count[TempArray[i]]] = TempArray[i];
}

template <class Record>
class RadixSorter: public Sorter<Record, Compare>
{
public:
	void RadixSort(Record Array[], int n, int d, int r);
};

template <class Record>
void RadixSorter<Record>::RadixSort( Record Array[], int n, int d, int r )
{//n为数组长度，d为排序码数，r为基数
	Record* TempArray = new Record[n];
	int* count = new int[r]; // 计数器
	int i,j,k;
	int Radix = 1; //取Array[j]的第i位排序码
	for(i=1; i<=d; i++)//分别对第i个排序码进行桶排序
	{
		for(j=0; j<r; j++) //初始计数器均为0
			count[j] = 0;
		for(j=0; j<n; j++)
		{
			//取Array[j]的第i位排序码
			k = (Array[j]/Radix)%r;
			count[k]++; //相应计数器加1
		}
		//将TempArray中的位置依次分配给r个桶
		for(j=1; j<r; j++)
			count[j] = count[j-1] + count[j];
		//将所有桶中的记录依次收集到TempArray中
		for(j=n-1; j>=0; j--)
		{
			//取Array[j]的第i位排序码
			k = (Array[j]/Radix)%r;
			//从第k个桶取出一个记录，计数器减1
			count[k]--;
			TempArray[count[k]] = Array[j];
		}
		//将临时数组中的内容复制到Array中
		for(j=0; j<n; j++)
			Array[j] = TempArray[j];
		Radix*=r;
	}
}

//静态队列

class Node{//结点类
public:
	int key; // 结点的关键码
	int next;// 下一个结点在数组中的下标
};

class StaticQueue{//静态队列类
public:
	int head;
	int tail;
};

template <class Record>
class LinkRadixSorter{
	//基于静态链的基数排序类
private:
	//分配过程
	void Distribute(Node* Array, int first, int i, int r, StaticQueue* queue);
	//收集过程
	void Collect(Node* Array, int& first, int i, int r, StaticQueue* queue);
	//输出序列
	void PrintArray(Node* A, int first);
public:
	void RadixSort(Node* Array, int n, int d, int r);
};

template <class Record>
void LinkRadixSorter<Record>::PrintArray( Node* A, int first )
{//first为静态链Array中第一个记录的下标
	int tmp; //用来扫描整个链的指针
	tmp = first;
	while(tmp != -1)
	{
		std::cout<<Array[tmp].key<<" ";
		tmp = Array[tmp].next;
	}
	std::cout<<'\n';
}

template <class Record>
void LinkRadixSorter<Record>::Collect( Node* Array, int& first, int i, int r, StaticQueue* queue )
{//Array中存放待排序记录，first为静态链中的第一个记录
	//i为第i个排序码，r为基数
	int last, k=0; // 已收集到得最后一个记录
	//找到第一个非空队列
	while(queue[k].head == -1)
		k++;
	first = queue[k].head;
	last = queue[k].tail;
	while(k<r-1) //继续收集下一个非空队列
	{
		k++;
		//找到下一个非空队列
		while(k<r-1 && queue[k].head == -1)
			k++;
		//将这个非空序列与上一个非空序列连接起来
		if(queue[k].head != -1)
		{
			Array[last].next = queue[k].head;
			//此时最后一个记录为该序列的尾部记录
			last = queue[k].tail;
		}
	}
	Array[last].next = -1; //收集完毕
}

template <class Record>
void LinkRadixSorter<Record>::Distribute( Node* Array, int first, int i, int r, StaticQueue* queue )
{
	//初始化r个队列
	for(int j=0; j<r; j++)
		queue[j].head = -1;
	//对整个静态链进行分配
	while(first != -1)
	{
		//取第i位排序码数字
		int k = Array[first].key;
		for(int a=0; a<i; a++)
			k = k/r;
		k = k%r;
		//把Array[first]分配到第k个子序列中，
		//如果子序列为空，Array[first]就是第一个记录
		if(queue[k].head == -1)
			queue[k].head = first;
		else //否则加到子序列的尾部
			Array[queue[k].tail].next = first;
		//first为子序列的尾部
		queue[k].tail = first;
		//继续分配下一个记录
		first = Array[first].next;
	}
}

template <class Record>
void LinkRadixSorter<Record>::RadixSort( Node* Array, int n, int d, int r )
{//n为数组长度，d为排序码个数，r为基数
	int first = 0; // first指向静态链中的第一个记录
	StaticQueue* queue;
	//存放r个桶的静态队列
	queue = new StaticQueue[r];
	//建链，初始为next域指向下一个记录
	for(int i=0; i<n; i++)
		Array[i].next = i+1;
	Array[n-1].next = -1; // 链表尾next为空
	cout<<"排序前： "<<endl;
	PrintArray(Array, 0); //输出原始序列
	//对第j个排序码进行分配和收集，一共d趟
	for(int j=0; j<d; j++)
	{
		Distribute(Array, first, j, r, queue);
		Collect(Array, first, j, r, queue);
	}
	cout<<"排序后："<<endl;
	PrintArray(Array, first);
	delete[] queue;
}

#endif