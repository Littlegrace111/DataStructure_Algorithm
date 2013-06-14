/**********************************************************
*file name: recursion_example.c
*date:      2013-1-18:9:30
*version:   1.0
*author:    Grace Wu
**********************************************************/

#include <stdio.h>

//-------------------------declarations--------------------------//
//阶乘递归实现
static long factorial(const long n);

//阶乘的尾递归形式，尾递归是对一般普通递归在栈上空间的优化
static long factorial_tail(const long n, const int a);

//斐波那契
static long fibonacci(const long n);
//---------------------------------------------------------------//

//以下的递归函数都没有考虑n<0的情况
//一是，保持代码整洁和代码效率，需要函数外围的调用者来检测
//把检测n是否合法的负担转移给调用者
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

