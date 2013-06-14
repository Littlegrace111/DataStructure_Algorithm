#include <windows.h>
#include <iostream>
#include <string>
#include "..\Common\MemoryLeakTest.h"
#include "..\LinkerList\Queue.h"
using namespace std;

void SLinkInsertTest();
void Polynomial_Test();
void Joseph();
void InOrderToPostOrder( __in char* InOrderString, __out char* PostOrderString);
void _InOrderToPostOrder(__in  char* InOrderString,__out char* PostOrderString);
void TestQueue();

void TestQueue()
{
	CQueue<int> queue;
	queue.EnQueue(1);
	queue.EnQueue(2);
	queue.EnQueue(3);

	while(!queue.IsEmpty())
		cout<<queue.DeQueue()<<endl;
}

void move(char from, char to){
	static int steps = 1;
	printf("%d: %c -> %c\n", steps++, from, to);
}

void hanio(int n, char from, char via, char to){
	if(n == 1){
		move(from, to);
		return;
	}
	hanio(n-1, from, to, via);
	move(from, to);
	hanio(n-1, via, from, to);
}

//朴素的字符串匹配法
//不对参数进行可用性检测
//在str中找到substr
void strstr(char* str, char* substr)
{
	int i = 0;
	char* p = str;
	char* q = substr;
	while( *p!='\0')
	{
		while((*q!='\0') && (*p == *q)){
			q++;
			p++;
		}
	}
}

void main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	cout<<"single linker test: press a"<<endl;
	cout<<"polynomial test: press b"<<endl;
	cout<<"Joseph test: press c"<<endl;
	cout<<"Hanoi test: press d"<<endl;
	cout<<"Expression transaction: press e"<<endl;
	cout<<"queue test: press f"<<endl;

	char choose;
	while(cin>>choose){
		switch (choose)
		{
		case 'a':
			SLinkInsertTest();
			break;
		case 'b':
			Polynomial_Test();
			break;
		case 'c':
			Joseph();
			break;
		case 'd':
			int n;
			cin>>n;
			hanio(n, 'A', 'B', 'C');
			break;
		case 'e':
			{
				char InOrder[100] = {0};
				char PostOrder[100] = {0};
				strcpy_s(InOrder, "4*c*(2*a+b)-c");
				cout<<"InOdrer: "<<InOrder<<endl;
				_InOrderToPostOrder(InOrder, PostOrder);
				cout<<"PostOrder: "<<PostOrder<<endl;
				break;
			}	
		case 'f':
			TestQueue();
			break;
		}
	}
	
	system("pause");
	return;
}