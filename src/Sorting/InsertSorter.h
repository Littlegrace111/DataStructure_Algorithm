#ifndef _INSERTSORTER_H
#define _INSERTSORTER_H

#include "Sorter.h"

template <class Record, class Compare>
class InsertSorter: public Sorter<Record, Compare>
{

};

template <class Record, class Compare>
class StraightInsertSorter: public InsertSorter<Record, Compare>
{//ֱ�Ӳ���������
public:
	void StraightInsertSort(Record Array[], int n);
};

template <class Record, class Compare>
void StraightInsertSorter<Record, Compare>::StraightInsertSort( Record Array[], int n )
{
	for(int i=1; i<n; i++)
	{//������ǰ��ļ�¼���бȽϣ��������þͽ���
		for(int j=i; j>0; j--){
			if(Compare::lt(Array[j], Array[j-1]))
				swap(Array, j, j-1);
			else
				break; //��ʱiǰ���¼���ź�
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
		//��i��ʼ��ǰѰ�Ҽ�¼i����ȷλ��
		int j = i-1;
		//����Щ���ڵ��ڼ�¼i�ļ�¼����
		while((j>=0)&&(Compare::lt(TempRecord, Array[j])))
		{
			Array[j+1] = Array[j];
			j = j-1;
		}
		//��ʱj������Ǽ�¼i����ȷλ�ã�����
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
	//��¼���ź������е����ҡ��е�λ��
	int left, right, middle;
	//���β����i����¼
	for(int i=1; i<n; i++){
		//���浱ǰ�������¼
		TempRecord = Array[i];
		left = 0;
		right = i-1;
		//��ʼ���Ҵ������¼����ȷλ��
		while(left <= right){
			middle = (left + middle)/2;
			//����������¼���м��¼С��������һ���в��ң���������һ���в���
			if(Compare::lt(TempRecord, Array[middle]))
				right = middle-1;
			else
				left = middle+1;
		}
		//��ǰ�����д��ڵ�ǰ�������¼�ļ�¼����
		for(int j=i-1; j>=left; j--)
			Array[j+1] = Array[j];
		//���������¼�����ȷλ��
		Array[left] = TempRecord;
	}
}

#endif