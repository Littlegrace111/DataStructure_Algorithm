#include <iostream>
#include "..\LinkerList\CLinker.h"

using namespace std;

//����������Լɪ��
//��n�������һ��Ȧ����1��ʼ��������������m(m<n)ʱ����m���˻ᱻ
//�����ɱ����ʣ�µ����ִ�1��ʼ���������մ˹�����ȥ��ʣ�����һ��
//�˵�ʱ��ֹͣ���Ǹ��˾����Ҵ��ߣ��ҳ�����Ҵ��ߵ��ʼ��λ�á�
void Joseph()
{
	int n = 0, m = 0;
	cout<<"input the amount of total people:"<<endl;
	cin>>n;
	cout<<"input the number of dead"<<endl;
	cin>>m;

	if(m>n){
		cout<<"m is larger than n"<<endl;
		return;
	}

	CLinker<int> clink;
	//��ʼ�����к����б�
	for(int i=1; i<=n; i++)
		clink.AddTail(i);
	clink.Debug_print();

	int j = 0, number = 0;
	do{
		++j;
		number = clink.GetNext();//��һ�η���ͷ�ڵ�
		if(j == m)
		{
			cout<<"��"<<number<<"���˱�ɱ��"<<endl;
			clink.RemoveAt(clink.GetCurrentIndex());
			j = 0;
		}
	}while(1 != clink.GetCount());

	cout<<"�Ҵ��ߣ�";
	clink.Debug_print();
}