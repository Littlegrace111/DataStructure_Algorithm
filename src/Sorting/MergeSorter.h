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

//�鲢����
template <class Record, class Compare>
void TwoWayMergeSorter<Record, Compare>::Merge( Record Array[], Record TempArray[], int left, int right, int middle )
{
	//�������ݴ�����ʱ����
	for(int j=left; j<=right; j++)
		TempArray[j] = Array[j];
	int index1 = left; //��������е���ʼλ��
	int index2 = middle+1; //����������ʼλ��
	int i = left;    //����ʼ�鲢
	while(index1 <= middle && index2 <= right)
	{
		//ȡ��С�߲���ϲ�������
		if(Compare::lt(TempArray[index1], TempArray[index2]))
			Array[i++] = TempArray[index1++];
		else
			Array[i++] = TempArray[index2++];
	}
	//����ʣ���¼
	while(index1 <= middle)
		Array[i++] = TempArray[index1++];
	while(index2<= right)
		Array[i++] = TempArray[index2++];
}

template <class Record, class Compare>
void TwoWayMergeSorter<Record, Compare>::MergeSort( Record Array[], Record TempArray[], int left, int right )
{
	//���������ֻ��0��1����¼
	if(left < right)
	{
		//���м仮��Ϊ����������
		int middle = (left+right)/2;
		//�����һ����еݹ�
		MergeSort(Array, TempArray, left, middle);
		//���ұ�һ����еݹ�
		MergeSort(Array, TempArray, middle+1, right);
		//���й鲢
		Merge(Array, TempArray, left, right, middle);
	}
}

//�Ż��Ĺ鲢����
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
	for(i=left; i<=middle; i++)//������ߵ�������
		TempArray[i] = Array[i];
	//�����ұߵ������У���˳��ߵ�����
	for(j=1; j<=right-middle; j++)
		TempArray[right-j+1] = Array[j+middle];
	//��ʼ�鲢
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
	//������г��ȴ�����ֵ��16��ѣ��������ݹ�
	if(right-left+1 > THRESHOLD_MERGE)
	{
		int middle = (left + right)/2; //���м仮��
		DoSort(Array, TempArray, left, middle);
		DoSort(Array, TempArray, middle+1, right);
		Merge(Array, TempArray, left, right, middle);
	}
}

template <class Record, class Compare>
void ImprovedTwoWayMergeSorter<Record, Compare>::MergeSort( Record Array[], Record TempArray[], int left, int right )
{
	DoSort(Array, TempArray, left, right);
	//�����������н�������ֱ�Ӳ�������
	ImprovedInsertSorter<Record, Compare> insert_sorter;
	insert_sorter.ImprovedInsertSort(&Array[left], right-left+1);
}

#endif