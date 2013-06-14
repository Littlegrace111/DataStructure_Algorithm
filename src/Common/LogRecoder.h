// **********************************************************************
//
// Copyright (c) 2003-2009 CyberGreatwall, Inc. All rights reserved.
//
// Author  ：Ding YL
// Date    ：2009-05-04
// Version ：1.0
// Revision :2012-11-16 8:48
// **********************************************************************

#ifndef _LOG_RECORDER_H
#define _LOG_RECORDER_H

#pragma warning(disable:4996)


#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	//
	//使用方法：1.修改日志等级以及文件名称符合需要
	//		   2.调用格式化打印：
	//			cyber_debug_f(fmt,...); //打印调试信息
	//			cyber_log_f(fmt,...);//打印提示信息，例如运行成功等
	//			cyber_error_f(fmt,...);//打印错误信息，包括错误定位
	//

	/***************************************************
	*定义日志等级：
	*	0-不打印(写入文件)任何信息
	*	1-打印日志和错误信息，建议在发行版中使用，默认值
	*	2-打印调试信息以及1的信息，建议在开发时使用
	*注：你可以根据需要修改此日志等级
	***************************************************/
#ifndef CYBER_LOG_LEVEL
#define		CYBER_LOG_LEVEL		1
#endif
	/***************************************************
	*定义日志文件名
	*注：你可以修改此文件名，但要确保此文件有创建以及写入权限
	/**************************************************/

#ifndef CYBER_LOG_FILE_NAME
#define		CYBER_LOG_FILE_NAME		"C:\\Logs\\LogRecoder.log"
#endif // CYBER_LOG_FILE_NAME


	//////////////////////////////////////////////////////////////////////////
	//
	//请不要随意修改下面的内容！
	//
	//////////////////////////////////////////////////////////////////////////
#define		LOG_FILE_SIZE			1024*1024*2 //日志文件的总大小不超过2M
#define		MAX_LOG_SIZE			2048 //每次记录的长度不超过2K

#if CYBER_LOG_LEVEL == 0
#define CYBER_LOG_LOW
#elif CYBER_LOG_LEVEL == 1
#define LOG_NORMAL
#elif CYBER_LOG_LEVEL == 2
#define CYBER_LOG_HIGH
#else
#error "Hi,you defined a wrong log level."
#endif

	//定义在文件中用于等级提示的宏

#define		CYBER_INFO_TIPS		"信息"
#define		CYBER_ERROR_TIPS	"错误"
#define		CYBER_DEBUG_TIPS	"调试"

#pragma warning(disable:4996)
static void RecordLog(BOOL date,char* tips,char *loginfo);


#define  log_notime_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(FALSE,CYBER_INFO_TIPS,Log_Buffer);}  //added by taotianyi
#define  log_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(TRUE,CYBER_INFO_TIPS,Log_Buffer);}
#define  error_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(TRUE,CYBER_ERROR_TIPS,Log_Buffer);}
#define  debug_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(TRUE,CYBER_DEBUG_TIPS,Log_Buffer);}
#define  info_notime_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(FALSE,NULL,Log_Buffer);}

	/*
	*记录信息到文件中
	*date: true则打印日期信息，false不打印
	*tips：打印的提示信息内容，例如信息，错误等
	*loginfo:用户输入的信息内容，最长不超过MAX_LOG_SIZE-60
	*$$注：出于效率上的考虑，没有做长度上的判断
	*返回值：无
	*日期：2009-05-02 Ding YL
	*/

	//static 关键字总结
	//1. 隐藏：当同时编译多个文件时，所有未加static前缀的全局变量和函数都具有全局可见性；
	//   变量或函数加了static，就会对其它源文件隐藏，利用这一特性可以在不同的文件中定义同名函数和同名变量，而不必担心命民冲突。
	//   static可以用作函数和变量的前缀，对于函数来讲，static的作用仅限于隐藏。
	//2. 保持变量内容的持久：存储在静态数据区的变量会在程序刚开始运行的时候就完成初始化工作，也是唯一的一次初始化；
    //   共有两种变量存储在静态存储区：全局变量和static变量；如果作为static局部变量在函数内定义，它的生存期是这个源程序，但是其作用域仁和自动变量相同，
    //   只能在定义该变量的函数内使用该变量，退出函数后，尽管该变量继续存在，但是不能使用它。
	static bool IsDirectory(LPCSTR pszDir)   
	{   
		DWORD dwAttr;   
		dwAttr = GetFileAttributes(pszDir);   
		if(dwAttr == -1L) //pszDir所指目标不存在
			return false;  
		if(dwAttr & FILE_ATTRIBUTE_DIRECTORY) //pszDir所指目标是文件夹
			return true;  
		return false;//pszDir所指目标是文件
	} 

	static void RecordLog(BOOL date,char* tips,char *loginfo)
	{
		struct tm *ts = NULL;
		time_t t = 0;
		char temp[MAX_LOG_SIZE];
		FILE *hFile = NULL;

		memset(temp, 0, MAX_LOG_SIZE);
		t = time(NULL);
		ts = localtime(&t);

		//标准打印信息，带有时间
		if (date)
		{
			sprintf_s(temp, MAX_LOG_SIZE,"[%4d-%2d-%2d %2d:%2d:%2d %s]%s\n", ts->tm_year+1900,
				ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec,
				tips,
				loginfo);
		}else
		{
			sprintf_s(temp, MAX_LOG_SIZE,"%s\n",
				loginfo);
		}

		if (!IsDirectory(CYBER_LOG_FILE_NAME)) {
			// 文件夹不存在
			CreateDirectory(CYBER_LOG_FILE_NAME, NULL);
		}

		hFile = fopen(CYBER_LOG_FILE_NAME,"at");
		if(hFile)
		{
			int pos = 0;
			fseek(hFile, 0, SEEK_END);
			pos = ftell( hFile );
			if (pos >= LOG_FILE_SIZE)//保证最大文件大小为LOG_FILE_SIZE
			{
				fclose(hFile);
				hFile = fopen(CYBER_LOG_FILE_NAME, "w");
			}
			fwrite(temp, 1, strlen(temp), hFile);
			fclose(hFile);
		}
	}

#ifdef CYBER_LOG_LOW
#define cyber_debug_f(fmt,...){}
#define cyber_log_f(fmt,...) {}
#define cyber_error_f(fmt,...){}
#elif defined LOG_NORMAL
#define debug_f(fmt,...){}
#define log_f(fmt,...) {log_record_f(fmt,__VA_ARGS__)}
#define error_f(fmt,...) {error_record_f(fmt,__VA_ARGS__);info_notime_record_f("来自：%s:%d",__FILE__,__LINE__)}
#elif defined CYBER_LOG_HIGH
#define cyber_debug_f(fmt,...){debug_record_f(fmt,__VA_ARGS__)}
#define cyber_log_f(fmt,...) {log_record_f(fmt,__VA_ARGS__)}
#define cyber_log_notime_f(fmt,...) {log_notime_record_f(fmt,__VA_ARGS__)}
#define cyber_error_f(fmt,...) {error_record_f(fmt,__VA_ARGS__);info_notime_record_f("来自：%s:%d",__FILE__,__LINE__)}
#endif

#define xassert(ex) ((ex)?((void)0):info_notime_record_f("%s:\n来自：%s:%d",#ex,__FILE__,__LINE__))

#ifdef __cplusplus
};
#endif // __cplusplus

#endif//End of _CYBER_LOGGER_H
