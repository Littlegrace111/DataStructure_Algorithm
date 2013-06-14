#include <iostream>
#include "..\LinkerList\CLinker.h"

using namespace std;

//问题描述：约瑟夫环
//有n个人组成一个圈，从1开始报数，报数报到m(m<n)时，报m的人会被
//无情地杀死，剩下的人又从1开始报数，按照此规则下去，剩下最后一个
//人的时候停止，那个人就是幸存者，找出这个幸存者的最开始的位置。
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
	//初始化序列号码列表
	for(int i=1; i<=n; i++)
		clink.AddTail(i);
	clink.Debug_print();

	int j = 0, number = 0;
	do{
		++j;
		number = clink.GetNext();//第一次返回头节点
		if(j == m)
		{
			cout<<"第"<<number<<"个人被杀死"<<endl;
			clink.RemoveAt(clink.GetCurrentIndex());
			j = 0;
		}
	}while(1 != clink.GetCount());

	cout<<"幸存者：";
	clink.Debug_print();
}