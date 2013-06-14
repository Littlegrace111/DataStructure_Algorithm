///////////////////////////////////////////////////////////////////////
//�㷨��
//1. ��������ǲ�����ʱ��ֱ�����
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

//������PostOrderString�ĳ����Ƿ����
//PostOrderString��Ҫ�����㹻�Ŀռ�
void InOrderToPostOrder(
	__in char* InOrderString,
	__out char* PostOrderString)
{
	char* Point = InOrderString;
	char* Ouput = PostOrderString;
	CStack<char> opertor_stack;

	while(*Point != '\0')
	{
		if(*Point >='0'&&*Point<='9' || *Point>='a'&&*Point<='z')//����ǲ�����ֱ�����
		{
			*Ouput = *Point;
			Ouput++;
		}else if(*Point == '+' ||
			     *Point == '-' ||
				 *Point == '*' ||
				 *Point == '/')//�Բ����������ȼ������ж�
		{
			char temp;
			if(opertor_stack.IsEmpty())//��ջΪ��ʱ��������Ӧ����ջ
				opertor_stack.push(*Point);
			else{
				opertor_stack.top(temp); //���ջ��Ԫ��
				if(temp != '(') //ջ��Ԫ�ز��ǿ�����
				{    //���ջ��Ԫ�ص����ȼ���������������������ȼ�
					 //ջ��Ԫ�س�ջ������Ԫ����ջ
					 if(GetOperatorPrivilege(temp)>= GetOperatorPrivilege(*Point))
					 {
						 opertor_stack.pop(temp);
						 *Ouput = temp;
						 Ouput++;
						 opertor_stack.push(*Point);
					 }else{//ջ��Ԫ�����ȼ���������Ԫ�����ȼ�������Ԫ����ջ
						 opertor_stack.push(*Point);
					 }
				}else{//���ջ��Ԫ���ǿ�����
					opertor_stack.push(*Point);
				}
			}
		}else if(*Point == '(') {//�����ǿ����ţ���ջ
			opertor_stack.push(*Point);
		}else if(*Point == ')')//�������Ԫ���Ǳ�����
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
				if(opertor_stack.IsEmpty())//��ջΪ��ʱ��������Ӧ����ջ
				{
					opertor_stack.push(*Point);
				}else{
					opertor_stack.top(temp); //���ջ��Ԫ��
					if(temp != '(') //ջ��Ԫ�ز��ǿ�����
					{    //���ջ��Ԫ�ص����ȼ���������������������ȼ�
						//ջ��Ԫ�س�ջ������Ԫ����ջ
						if(GetOperatorPrivilege(temp)>= GetOperatorPrivilege(*Point))
						{
							opertor_stack.pop(temp);
							*Ouput = temp;
							Ouput++;
							opertor_stack.push(*Point);
						}else{//ջ��Ԫ�����ȼ���������Ԫ�����ȼ�������Ԫ����ջ
							opertor_stack.push(*Point);
						}
					}else{//���ջ��Ԫ���ǿ�����
						opertor_stack.push(*Point);
					}
				}
			}
			
			break;
		case '('://�����ǿ����ţ���ջ
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
	//�������ջ�еĶ���
	char temp;
	while(!opertor_stack.IsEmpty())
	{
		opertor_stack.pop(temp);
		*Ouput = temp;
		Ouput++;
	}
}