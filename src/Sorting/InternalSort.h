#ifndef _INTERNAL_SORTING_H
#define _INTERNAL_SORTING_H
#include <iostream>

template<class Record, class Compare>
class Sorter{
protected:
	//���������е�����Ԫ��
	static void swap(Record Array[], int i, int j);
public:
	//������Array��������
	void Sort(Record Array[], int n);
	//�����������
	void PrintArray(Record array[], int n);
};

template<class Record, class Compare>
void Sorter<Record, Compare>::PrintArray( Record array[], int n )
{
	//�����������
	for(int i=0; i<n; i++)
		std::cout<<array[i]<<" ";
	std::cout<<endl;
}

template<class Record, class Compare>
void Sorter<Record, Compare>::swap( Record Array[], int i, int j )
{
	//���������е�����Ԫ��
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

//ֱ�Ӳ���������
template <class Record, class Compare>
class StraightInsertSorter: public InsertSorter<Record, Compare>{
public:
	void Sort(Record Array[], int n);
};

//ֱ�Ӳ�������
//������������ļ�¼��ÿ���¼�¼��Ҫ��ǰ����Щ���ź���ļ�¼���бȽϣ�Ȼ����뵽�ʵ���λ�á�
//�ȶ�
//�ռ���ۣ�O(1)
//ʱ����ۣ�
//  ��������n-1�αȽϣ�0�αȽϣ�
//  ���������ȽϺͽ�������ΪO(n^2);
template <class Record, class Compare>
void StraightInsertSorter<Record, Compare>::Sort( Record Array[], int n )
{//Array[]Ϊ���������飬 nΪ���鳤��
	for(int i=1; i<n; i++){//���β����i¼
		for(int j=i; j>0; j--){
			if(Compare::lt(Array[j], Array[j-1]))
				swap(Array, j, j-1);
			else break;
		}
	}
}

//�Ż��Ĳ���������
template<class Record, class Compare>
class ImprovedInsertSorter: public InsertSorter<Record, Compare>
{
public:
	void Sort(Record Array[], int n);
};

//�Ż��Ĳ��������㷨
template<class Record, class Compare>
void ImprovedInsertSorter<Record, Compare>::Sort( Record Array[], int n )
{
	Record TempRecord;  //��ʱ����
	for(int i=1; i<n; i++){
		TempRecord = Array[i];
		//��i��ʼ��ǰѰ�Ҽ�¼i����ȷλ��
		int j = i-1;
		//����Щ���ڵ��ڼ�¼i�ļ�¼����
		while((j>=0)&&(Compare::lt(TempRecord, Array[j])))
		{
			Array[j+1] = Array[j];
			j--;
		}
		//��ʱj������Ǽ�¼i����ȷλ�ã�����
		Array[j+1] = TempRecord;
	}
}


//���ַ���������
//�ڲ����i����¼ʱ��ǰ��ļ�¼�Ѿ�������ģ�
//�����ö��ַ����ҵ�i����¼����ȷλ�á�
template <class Record, class Compare>
class BinaryInsertSorter: public InsertSorter<Record, Compare>
{
public:
	void Sort(Record Array[], int n);
};

//�㷨������
//�ȶ�
//�ռ���ۣ�O(1)
//ʱ����ۣ�
//   ����ÿ����¼��ҪO(log i)�αȽ�
//   ����ƶ�i+1�Σ�����2�Σ��ƶ���ʱ��¼��
//   �������������ʱ�����ΪO(nlogn)
//   ����ƽ���������ΪO(n^2)
template <class Record, class Compare>
void BinaryInsertSorter<Record, Compare>::Sort( Record Array[], int n )
{
	//Array[] Ϊ���������飬nΪ���鳤��
	Record TempRecord; 
	//��¼�Ѿ��ź������е����ң���λ��
	int left, right, middle;
	//���β����i����¼
	for(int i=1; i<n; i++)
	{
		//���浱ǰ������ļ�¼
		TempRecord = Array[i];
		//��¼���ź������е�����λ��
		left = 0; right = i-1;
		//��ʼ���Ҵ������¼����ȷλ��
		while(left <= right){
			//�м�λ��
			middle = (left + right)/2;
			//����������¼���м��¼С��������һ���в��ң�
			//���������һ���в���
			if(Compare::lt(TempRecord, Array[middle]))
				right = middle -1;
			else 
				left = middle -1;
		}
		//��ǰ�����д��ڵ�ǰ�������¼�ļ�¼����
		for(int j=i-1; j>=left; j--)
			Array[j+1] = Array[j];
		//���������¼�����ȷ��λ��
		Array[left] = TempRecord;
	}
}

//ð������
//��ͣ�Ƚ����ڵļ�¼���������������Ҫ�󣬾ͽ������ڼ�¼��֪�����еļ�¼���Ѿ��ź���
template <class Record, class Compare>
class BubbleSorter: public Sorter<Record, Compare>
{//ð��������
public:
	void Sort(Record Array[], int n);
};

//�ȶ�
//�ռ���ۣ� O(1)
//ʱ����ۣ�O(n^2)
template <class Record, class Compare>
void BubbleSorter<Record, Compare>::Sort( Record Array[], int n )
{
	//��i����¼ð��
	for(int i=1; i<n; i++)//���αȽ����ڼ�¼������������ã��ͽ���
		for(int j=n-1; j>=i; j--)
			if(Compare::lt(Array[j], Array[j-1]))
				swap(Array, j, j-1);
}

//�Ż���ð������
//�Ľ������ÿ��ð�ݹ������Ƿ��������������û�У���������������Ѿ��ź����ˣ��������
//���ⲻ��Ҫ�ıȽ�
template <class Record, class Compare>
class ImporvedBubbleSorter: public Sorter<Record, Compare>
{
public:
	void Sort(Record, Array[], int n);
};

template <class Record, class Compare>
void ImporvedBubbleSorter<Record, Compare>::Sort( Record, Array[], int n )
{
	bool NoSwap; // �Ƿ��������ı�־
	for(int i=1; i<n; i++)
	{
		NoSwap = true;
		for(int j=n-1; j>=i; j--)
			if(Compare::lt(Array[j], Array[j-1]))
			{
				swap(Array, j, j-1);
				NoSwap = false;//��������˽�������־��Ϊ��
			}
		//���û�з�����������ʾ���ź��򣬽����㷨
		if(NoSwap)
			return;
	}
}

//ֱ��ѡ������
//�ҳ�ʣ�µ�δ�����¼�е���С��¼��Ȼ��ֱ���������е�i����¼������
//��ð������������ƶ�����
template <class Record, class Compare>
class StraightSelectSorter: public Sorter<Record, Compare>
{
public:
	void Sort(Record Array[], int n);
};

//���ȶ�
//�ռ���ۣ�O(1)
//ʱ����ۣ�O��n^2��
template<class Record, class Compare>
class StraightSelectSorter: public Sorter<Record, Compare>
{
	//����ѡ����iС�ļ�¼����ʣ���¼����С���Ǹ�
	for(int i=0; i<n-1; i++)
	{
		//���ȼ����¼i������С��
		int Smallest = i;
		//��ʼ���ɨ������ʣ���¼
		for(int j=i+1; j<n; j++)
			if(Compare::lt(Array[j], Array[Smallest]))
				Smallest = j;
		//����iС�ļ�¼���������е�i��λ��
		swap(Array, i, Smallest);
	}
};
#endif 