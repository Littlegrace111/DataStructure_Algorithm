#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>

//////////////////////////////////////////////////
//在debug模式下，启用断言调试
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
//非常好用！！！
//memory leak test
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
///////////////////////////////////////////////////

//使用方法：
//在.cpp文件中包含以下代码，debug时Output就能检测memoryLeak
//内存泄漏检测机制
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);