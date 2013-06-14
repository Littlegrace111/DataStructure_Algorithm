///////////////////////////////////////////////////////////////////////
//算法：
//1. 当输入的是操作数时，直接输出
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "..\LinkerList\Stack.h"
using namespace std;

static int GetOperatorPrivilege(const char& Opertor)
{
	switch(Opertor)
	{
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	default:  return 0;
	}
}

//不考虑PostOrderString的长度是否溢出
//PostOrderString需要给出足够的空间
void InOrderToPostOrder(
	__in char* InOrderString,
	__out char* PostOrderString)
{
	char* Point = InOrderString;
	char* Ouput = PostOrderString;
	CStack<char> opertor_stack;

	while(*Point != '\0')
	{
		if(*Point >='0'&&*Point<='9' || *Point>='a'&&*Point<='z')//如果是操作数直接输出
		{
			*Ouput = *Point;
			Ouput++;
		}else if(*Point == '+' ||
			     *Point == '-' ||
				 *Point == '*' ||
				 *Point == '/')//对操作符的优先级进行判断
		{
			char temp;
			if(opertor_stack.IsEmpty())//当栈为空时，操作符应该入栈
				opertor_stack.push(*Point);
			else{
				opertor_stack.top(temp); //获得栈顶元素
				if(temp != '(') //栈顶元素不是开括号
				{    //如果栈顶元素的优先级不低于输入运算符的优先级
					 //栈顶元素出栈，输入元素入栈
					 if(GetOperatorPrivilege(temp)>= GetOperatorPrivilege(*Point))
					 {
						 opertor_stack.pop(temp);
						 *Ouput = temp;
						 Ouput++;
						 opertor_stack.push(*Point);
					 }else{//栈顶元素优先级低于输入元素优先级，输入元素入栈
						 opertor_stack.push(*Point);
					 }
				}else{//如果栈顶元素是开括号
					opertor_stack.push(*Point);
				}
			}
		}else if(*Point == '(') {//输入是开括号，入栈
			opertor_stack.push(*Point);
		}else if(*Point == ')')//如果输入元素是闭括号
		{
			char temp;
			opertor_stack.top(temp);
			while(temp != '(')
			{
				opertor_stack.pop(temp);
				*Ouput = temp;
				Ouput++;
				opertor_stack.top(temp);
			}
			opertor_stack.pop(temp);
		}
		++Point;
	}

	char temp;
	while(!opertor_stack.IsEmpty())
	{
		opertor_stack.pop(temp);
		*Ouput = temp;
		Ouput++;
	}
}

void _InOrderToPostOrder(
	__in  char* InOrderString,
	__out char* PostOrderString)
{
	char* Point = InOrderString;
	char* Ouput = PostOrderString;
	CStack<char> opertor_stack;
	while(*Point != '\0')
	{
		switch(*Point)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			{
				char temp;
				if(opertor_stack.IsEmpty())//当栈为空时，操作符应该入栈
				{
					opertor_stack.push(*Point);
				}else{
					opertor_stack.top(temp); //获得栈顶元素
					if(temp != '(') //栈顶元素不是开括号
					{    //如果栈顶元素的优先级不低于输入运算符的优先级
						//栈顶元素出栈，输入元素入栈
						if(GetOperatorPrivilege(temp)>= GetOperatorPrivilege(*Point))
						{
							opertor_stack.pop(temp);
							*Ouput = temp;
							Ouput++;
							opertor_stack.push(*Point);
						}else{//栈顶元素优先级低于输入元素优先级，输入元素入栈
							opertor_stack.push(*Point);
						}
					}else{//如果栈顶元素是开括号
						opertor_stack.push(*Point);
					}
				}
			}
			
			break;
		case '('://输入是开括号，入栈
			opertor_stack.push(*Point);
			break;
		case ')':
			{
				char temp;
				opertor_stack.top(temp);
				while(temp != '(')
				{
					opertor_stack.pop(temp);
					*Ouput = temp;
					Ouput++;
					opertor_stack.top(temp);
				}
				opertor_stack.pop(temp);
			}
			
			break;
		default:
			*Ouput = *Point;
			Ouput++;
		}
		++Point;
	}
	//输出其余栈中的东西
	char temp;
	while(!opertor_stack.IsEmpty())
	{
		opertor_stack.pop(temp);
		*Ouput = temp;
		Ouput++;
	}
}