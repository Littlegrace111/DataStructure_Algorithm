#ifndef _QUICKSORTER_H
#define _QUICKSORTER_H

#include "Sorter.h"
#include "InsertSorter.h"

template<class Record, class Compare>
class QuickSorter:public Sorter<Record, Compare>
{
protected:
	int SelectPivot(int left, int right);//ѡ����ֵ��������ֵ�±�
	int Partition(Record Array[], int left, int right);
public:
	void QuickSort(Record Array[], int left, int right);
};

template<class Record, class Compare>
int QuickSorter<Record, Compare>::Partition( Record Array[], int left, int right )
{//�ָ�����ָ����ֵ�ѵ�����ȷλ��
	Record TempRecord; //�����ֵ����ʱ����
	int i = left;
	int j = right;
	//����ֵ������ʱ����
	TempRecord = Array[j];
	//��ʼ�ָi��j�������м��ƶ���ֱ������
	while(i != j){
		//iָ�����ƣ�ֱ���ҵ�һ�����ڵ�����ֵ�ļ�¼
		while(Compare::lt(Array[i], TempRecord)&&(j>i))
			i++;
		//���i��jδ�����ͽ�����Ԫ�ػ����ұ߿��е�λ��
		if(i<j){
			Array[j] = Array[i];
			j--; //jָ������һ��
		}
		//jָ�����ƣ�ֱ���ҵ�һ��С�ڵ�����ֵ�ļ�¼
		while(Compare::gt(Array[j], TempRecord)&&(j>i))
			j--;
		//���i��jδ�����ͽ�����Ԫ�ػ�����߿���λ��
		if(i<j){
			Array[i] = Array[j];
			i++; //iָ��������һ��
		}
	}
	//����ֵ����ֽ�λ��i��
	Array[i] = TempRecord;
	return i;
}

template<class Record, class Compare>
int QuickSorter<Record, Compare>::SelectPivot( int left, int right )
{
	//������ֵ��
	return (left + right)/2;
}

template<class Record, class Compare>
void QuickSorter<Record, Compare>::QuickSort( Record Array[], int left, int right )
{//Array[]Ϊ���������飬i��j�ֱ�Ϊ��������
	//�����������ֻ��0��1����¼���Ͳ���Ҫ����
	if(right <= left)
		return;
	//ѡ����ֵ
	int pivot = SelectPivot(left, right);
	//�ָ�ǰ�Ƚ���ֵ�ŵ�����ĩ��
	swap(Array, pivot, right);
	//��ʣ��ļ�¼���зָ�
	pivot = Partition(Array, left, right);
	//����ֵ��ߵ������н��еݹ��������
	QuickSort(Array, left, pivot-1);
	//����ֵ�ұߵ������н��еݹ��������
	QuickSort(Array, pivot+1, right);
}


//�Ż��Ŀ�������
#define THRESHOLD 16

template<class Record, class Compare>
class ImprovedQuickSorter: public QuickSorter<Record, Compare>
{
private:
	//ѡ����ֵ��������ֵ�±�
	//int SelectPivot(int left, int right);
	//�ָ������ֵλ��
	//int Partition(Record Array[], int left, int right);
	void DoSort(Record Array[], int left, int right);
public:
	void QuickSort(Record Array[], int left, int right);
};

template<class Record, class Compare>
void ImprovedQuickSorter<Record, Compare>::DoSort( Record Array[], int left, int right )
{
	//���������ֻ��0��1����¼���Ͳ�������
	if(right <= left)
		return;
	//������г���С�ڵ�����ֵ��16��ѣ���ֹͣ�ָ������ݹ�
	if(right=left+1 > THRESHOLD)
	{
		//ѡ����ֵ
		int pivot = SelectPivot(left, right);
		//����ֵ��������ĩ��
		swap(Array, pivot, right);
		//��ʣ��ļ�¼���зָ�
		pivot = Partition(Array, left, right);
		//�Էָ���������н��еݹ��������
		//����ֵ���ҷֱ��������
		DoSort(Array, left, pivot-1);
		DoSort(Array,pivot+1, right);
	}
}

template<class Record, class Compare>
void ImprovedQuickSorter<Record, Compare>::QuickSort( Record Array[], int left, int right )
{   //�Ż��Ŀ�������Array[]Ϊ���������飬i��j�ֱ�Ϊ��������
	//�ȶ����н��еݹ�����
	DoSort(Array, left, right);
	//�����������н���һ��ֱ�Ӳ�������
	ImprovedInsertSorter<Record, Compare> insert_sort;
	insert_sort.ImprovedInsertSort(Array, right-left+1);
}

#endif