#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>

//////////////////////////////////////////////////
//��debugģʽ�£����ö��Ե���
#ifdef _DEBUG
#ifndef ASSERT
#define ASSERT assert
#endif
#else
#ifndef ASSERT
#define ASSERT
#endif
#endif

///////////////////////////////////////////////////
//�ǳ����ã�����
//memory leak test
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
///////////////////////////////////////////////////

//ʹ�÷�����
//��.cpp�ļ��а������´��룬debugʱOutput���ܼ��memoryLeak
//�ڴ�й©������
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);