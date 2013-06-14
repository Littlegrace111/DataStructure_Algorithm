/**********************************************************
*file name: recursion_example.c
*date:      2013-1-18:9:30
*version:   1.0
*author:    Grace Wu
**********************************************************/

#include <stdio.h>

//-------------------------declarations--------------------------//
//�׳˵ݹ�ʵ��
static long factorial(const long n);

//�׳˵�β�ݹ���ʽ��β�ݹ��Ƕ�һ����ͨ�ݹ���ջ�Ͽռ���Ż�
static long factorial_tail(const long n, const int a);

//쳲�����
static long fibonacci(const long n);
//---------------------------------------------------------------//

//���µĵݹ麯����û�п���n<0�����
//һ�ǣ����ִ�������ʹ���Ч�ʣ���Ҫ������Χ�ĵ����������
//�Ѽ��n�Ƿ�Ϸ��ĸ���ת�Ƹ�������
static long factorial(const long n)
{
	return 0 == n || 1 == n ? 1 : n * factorial(n - 1);
}

static long factorial_tail(const long n, const int a)
{
	return 0 == n || 1 == n ? 1 : factorial_tail(n-1, n*a);
}

static long fibonacci(const long n)
{
	return 0 == n || 1 == n ? 1 : (fibonacci(n - 1) + fibonacci(n - 2));
}

