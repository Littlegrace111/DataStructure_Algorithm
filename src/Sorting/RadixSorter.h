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
{//Ͱʽ����Array[]Ϊ���������飬���м�¼��λ������[0, max)��
	int* TempArray = new Record[n]; // ��ʱ����
	int* count = new int[max]; //С�ڵ���i��Ԫ�ظ���
	int i;
	//�������鵽��ʱ����
	for(i=0; i<n; i++)
		TempArray[i] = Array[i];
	//���м�������ʼ��Ϊ0
	for(i=0; i<max; i++)
		count[i] = 0;
	//ͳ��ÿ��ȡֵ���ֵĴ���
	for(i=0; i<n; i++)
		count[Array[i]]++;
	//ͳ��С�ڵ���i��Ԫ�ظ���
	for(i=1; i<max; i++)
		count[i] = count[i-1]+count[i];
	//��˳�������������
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
{//nΪ���鳤�ȣ�dΪ����������rΪ����
	Record* TempArray = new Record[n];
	int* count = new int[r]; // ������
	int i,j,k;
	int Radix = 1; //ȡArray[j]�ĵ�iλ������
	for(i=1; i<=d; i++)//�ֱ�Ե�i�����������Ͱ����
	{
		for(j=0; j<r; j++) //��ʼ��������Ϊ0
			count[j] = 0;
		for(j=0; j<n; j++)
		{
			//ȡArray[j]�ĵ�iλ������
			k = (Array[j]/Radix)%r;
			count[k]++; //��Ӧ��������1
		}
		//��TempArray�е�λ�����η����r��Ͱ
		for(j=1; j<r; j++)
			count[j] = count[j-1] + count[j];
		//������Ͱ�еļ�¼�����ռ���TempArray��
		for(j=n-1; j>=0; j--)
		{
			//ȡArray[j]�ĵ�iλ������
			k = (Array[j]/Radix)%r;
			//�ӵ�k��Ͱȡ��һ����¼����������1
			count[k]--;
			TempArray[count[k]] = Array[j];
		}
		//����ʱ�����е����ݸ��Ƶ�Array��
		for(j=0; j<n; j++)
			Array[j] = TempArray[j];
		Radix*=r;
	}
}

//��̬����

class Node{//�����
public:
	int key; // ���Ĺؼ���
	int next;// ��һ������������е��±�
};

class StaticQueue{//��̬������
public:
	int head;
	int tail;
};

template <class Record>
class LinkRadixSorter{
	//���ھ�̬���Ļ���������
private:
	//�������
	void Distribute(Node* Array, int first, int i, int r, StaticQueue* queue);
	//�ռ�����
	void Collect(Node* Array, int& first, int i, int r, StaticQueue* queue);
	//�������
	void PrintArray(Node* A, int first);
public:
	void RadixSort(Node* Array, int n, int d, int r);
};

template <class Record>
void LinkRadixSorter<Record>::PrintArray( Node* A, int first )
{//firstΪ��̬��Array�е�һ����¼���±�
	int tmp; //����ɨ����������ָ��
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
{//Array�д�Ŵ������¼��firstΪ��̬���еĵ�һ����¼
	//iΪ��i�������룬rΪ����
	int last, k=0; // ���ռ��������һ����¼
	//�ҵ���һ���ǿն���
	while(queue[k].head == -1)
		k++;
	first = queue[k].head;
	last = queue[k].tail;
	while(k<r-1) //�����ռ���һ���ǿն���
	{
		k++;
		//�ҵ���һ���ǿն���
		while(k<r-1 && queue[k].head == -1)
			k++;
		//������ǿ���������һ���ǿ�������������
		if(queue[k].head != -1)
		{
			Array[last].next = queue[k].head;
			//��ʱ���һ����¼Ϊ�����е�β����¼
			last = queue[k].tail;
		}
	}
	Array[last].next = -1; //�ռ����
}

template <class Record>
void LinkRadixSorter<Record>::Distribute( Node* Array, int first, int i, int r, StaticQueue* queue )
{
	//��ʼ��r������
	for(int j=0; j<r; j++)
		queue[j].head = -1;
	//��������̬�����з���
	while(first != -1)
	{
		//ȡ��iλ����������
		int k = Array[first].key;
		for(int a=0; a<i; a++)
			k = k/r;
		k = k%r;
		//��Array[first]���䵽��k���������У�
		//���������Ϊ�գ�Array[first]���ǵ�һ����¼
		if(queue[k].head == -1)
			queue[k].head = first;
		else //����ӵ������е�β��
			Array[queue[k].tail].next = first;
		//firstΪ�����е�β��
		queue[k].tail = first;
		//����������һ����¼
		first = Array[first].next;
	}
}

template <class Record>
void LinkRadixSorter<Record>::RadixSort( Node* Array, int n, int d, int r )
{//nΪ���鳤�ȣ�dΪ�����������rΪ����
	int first = 0; // firstָ��̬���еĵ�һ����¼
	StaticQueue* queue;
	//���r��Ͱ�ľ�̬����
	queue = new StaticQueue[r];
	//��������ʼΪnext��ָ����һ����¼
	for(int i=0; i<n; i++)
		Array[i].next = i+1;
	Array[n-1].next = -1; // ����βnextΪ��
	cout<<"����ǰ�� "<<endl;
	PrintArray(Array, 0); //���ԭʼ����
	//�Ե�j����������з�����ռ���һ��d��
	for(int j=0; j<d; j++)
	{
		Distribute(Array, first, j, r, queue);
		Collect(Array, first, j, r, queue);
	}
	cout<<"�����"<<endl;
	PrintArray(Array, first);
	delete[] queue;
}

#endif