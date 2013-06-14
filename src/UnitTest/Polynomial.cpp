#include <stdio.h>
#include <iostream>
#include "..\LinkerList\SLinker.h"

using namespace std;

#define Max(x, y) (((x)>(y))?(x):(y))

//P1(X) = X^2 + 2X + 3
//P2(X) = 3X^3 + 10X + 6
//加法
//P1(X) + P2(X) = (X^2 + 2X + 3) + (3X^3 + 10X + 6)
//              = 3X^3 + X^2 + 12X^1 + 9
//乘法
//P1(X) * P2(X) = (X^2 + 2X + 3) * (3X^3 + 10X + 6)
//              = 3X^5 + 6X^4 + 19X^2 + 26X^2 +42X^1 + 18

struct Polynomial{
	CSLinker<int> Coeff;
	int HighPower; // 记录最高指数
	Polynomial(int high = 0):HighPower(high){}
};


static void print_polynomial(Polynomial& poly)
{
	cout<<"P(X) = ";
	int temp = 0;
	int count = poly.HighPower;
	//逆序输出
	for(int i=count; i>=1; i--)
	{
		temp = poly.Coeff.GetAt(i);
		if(0 != temp) cout<<temp<<"X^"<<i<<" + ";
	}
	cout<<poly.Coeff.GetAt(0)<<endl;
}


static void AddPolynomial(
	Polynomial& polysum,
	const Polynomial& polyl,
	const Polynomial& polyr )
{
	int left = 0; 
	int right = 0;
	int sum = 0;

	polysum.HighPower = Max(polyl.HighPower, polyr.HighPower);
	for(int i=0; i<= polysum.HighPower; ++i)
	{
		left = polyl.Coeff.GetAt(i);
		right = polyr.Coeff.GetAt(i);
		sum = left + right;
		polysum.Coeff.AddTail(sum);
	}
}


static void MultiplePolynomial(
	Polynomial& polymul,
	const Polynomial& polyl,
	const Polynomial& polyr )
{
	polymul.HighPower = polyl.HighPower + polyr.HighPower;
	//初始化多项式乘法结果
	for(int i=0; i<=polymul.HighPower; i++)
	{
		polymul.Coeff.AddTail(0);
	}

	//int count = Max(polyl.HighPower, polyr.HighPower);
	int temp1 = 0, temp2 = 0;
	for(int i=0; i<=polyl.HighPower; i++)
	{
		temp1 = polyl.Coeff.GetAt(i);
		for(int j=0; j<=polyr.HighPower; j++)
		{
			temp2 = temp1 * polyr.Coeff.GetAt(j);
			temp2 = polymul.Coeff.GetAt(i+j) + temp2;
			polymul.Coeff.SetAt(i+j, temp2);
		}
	}
}


void Polynomial_Test()
{
	cout<<"start polynomial test"<<endl;
	Polynomial left(2), right(3), addres, mulres;
	//P1(X) = X^2 + 2X + 3
	left.Coeff.AddTail(3);
	left.Coeff.AddTail(2);
	left.Coeff.AddTail(1);
	left.Coeff.Debug_print();
	print_polynomial(left);
	
	//P2(X) = 3X^3 + 10X^2 + 6
	right.Coeff.AddTail(6);
	right.Coeff.AddTail(0);
	right.Coeff.AddTail(10);
	right.Coeff.AddTail(3);
	right.Coeff.Debug_print();
	print_polynomial(right);

	//result = 3X^3 + X^2 + 12X^1 + 9
	cout<<"the add operation:"<<endl;
	AddPolynomial(addres, left, right);
	addres.Coeff.Debug_print();
	print_polynomial(addres);
	
	//result = 3X^5 + 16X^4 + 29X^3 + 36X^2 + 12X + 18
	cout<<"the multiple operation:"<<endl;
	MultiplePolynomial(mulres, left, right);
	mulres.Coeff.Debug_print();
	print_polynomial(mulres);
	cout<<"end test"<<endl;
}

void SLinkInsertTest()
{
	cout<<"start single link unit test"<<endl;
	CSLinker<int> slink;
	for(int i=0; i<10; i++)
	{
		slink.AddTail(i);
	}
	slink.Debug_print();
	slink.AddHead(-1);
	slink.DeleteAt(0);
	slink.DeleteAt(1);
	slink.Debug_print();
	slink.DeleteAt(-1);
	slink.DeleteAt(10);
	slink.Debug_print();
	cout<<"end test"<<endl;
}