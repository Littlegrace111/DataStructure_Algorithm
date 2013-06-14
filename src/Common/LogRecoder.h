// **********************************************************************
//
// Copyright (c) 2003-2009 CyberGreatwall, Inc. All rights reserved.
//
// Author  ��Ding YL
// Date    ��2009-05-04
// Version ��1.0
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
	//ʹ�÷�����1.�޸���־�ȼ��Լ��ļ����Ʒ�����Ҫ
	//		   2.���ø�ʽ����ӡ��
	//			cyber_debug_f(fmt,...); //��ӡ������Ϣ
	//			cyber_log_f(fmt,...);//��ӡ��ʾ��Ϣ���������гɹ���
	//			cyber_error_f(fmt,...);//��ӡ������Ϣ����������λ
	//

	/***************************************************
	*������־�ȼ���
	*	0-����ӡ(д���ļ�)�κ���Ϣ
	*	1-��ӡ��־�ʹ�����Ϣ�������ڷ��а���ʹ�ã�Ĭ��ֵ
	*	2-��ӡ������Ϣ�Լ�1����Ϣ�������ڿ���ʱʹ��
	*ע������Ը�����Ҫ�޸Ĵ���־�ȼ�
	***************************************************/
#ifndef CYBER_LOG_LEVEL
#define		CYBER_LOG_LEVEL		1
#endif
	/***************************************************
	*������־�ļ���
	*ע��������޸Ĵ��ļ�������Ҫȷ�����ļ��д����Լ�д��Ȩ��
	/**************************************************/

#ifndef CYBER_LOG_FILE_NAME
#define		CYBER_LOG_FILE_NAME		"C:\\Logs\\LogRecoder.log"
#endif // CYBER_LOG_FILE_NAME


	//////////////////////////////////////////////////////////////////////////
	//
	//�벻Ҫ�����޸���������ݣ�
	//
	//////////////////////////////////////////////////////////////////////////
#define		LOG_FILE_SIZE			1024*1024*2 //��־�ļ����ܴ�С������2M
#define		MAX_LOG_SIZE			2048 //ÿ�μ�¼�ĳ��Ȳ�����2K

#if CYBER_LOG_LEVEL == 0
#define CYBER_LOG_LOW
#elif CYBER_LOG_LEVEL == 1
#define LOG_NORMAL
#elif CYBER_LOG_LEVEL == 2
#define CYBER_LOG_HIGH
#else
#error "Hi,you defined a wrong log level."
#endif

	//�������ļ������ڵȼ���ʾ�ĺ�

#define		CYBER_INFO_TIPS		"��Ϣ"
#define		CYBER_ERROR_TIPS	"����"
#define		CYBER_DEBUG_TIPS	"����"

#pragma warning(disable:4996)
static void RecordLog(BOOL date,char* tips,char *loginfo);


#define  log_notime_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(FALSE,CYBER_INFO_TIPS,Log_Buffer);}  //added by taotianyi
#define  log_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(TRUE,CYBER_INFO_TIPS,Log_Buffer);}
#define  error_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(TRUE,CYBER_ERROR_TIPS,Log_Buffer);}
#define  debug_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(TRUE,CYBER_DEBUG_TIPS,Log_Buffer);}
#define  info_notime_record_f(fmt,...) {char Log_Buffer[MAX_LOG_SIZE]; memset(Log_Buffer,0,MAX_LOG_SIZE);sprintf_s(Log_Buffer,MAX_LOG_SIZE,fmt,__VA_ARGS__);RecordLog(FALSE,NULL,Log_Buffer);}

	/*
	*��¼��Ϣ���ļ���
	*date: true���ӡ������Ϣ��false����ӡ
	*tips����ӡ����ʾ��Ϣ���ݣ�������Ϣ�������
	*loginfo:�û��������Ϣ���ݣ��������MAX_LOG_SIZE-60
	*$$ע������Ч���ϵĿ��ǣ�û���������ϵ��ж�
	*����ֵ����
	*���ڣ�2009-05-02 Ding YL
	*/

	//static �ؼ����ܽ�
	//1. ���أ���ͬʱ�������ļ�ʱ������δ��staticǰ׺��ȫ�ֱ����ͺ���������ȫ�ֿɼ��ԣ�
	//   ������������static���ͻ������Դ�ļ����أ�������һ���Կ����ڲ�ͬ���ļ��ж���ͬ��������ͬ�������������ص��������ͻ��
	//   static�������������ͱ�����ǰ׺�����ں���������static�����ý��������ء�
	//2. ���ֱ������ݵĳ־ã��洢�ھ�̬�������ı������ڳ���տ�ʼ���е�ʱ�����ɳ�ʼ��������Ҳ��Ψһ��һ�γ�ʼ����
    //   �������ֱ����洢�ھ�̬�洢����ȫ�ֱ�����static�����������Ϊstatic�ֲ������ں����ڶ��壬���������������Դ���򣬵������������ʺ��Զ�������ͬ��
    //   ֻ���ڶ���ñ����ĺ�����ʹ�øñ������˳������󣬾��ܸñ����������ڣ����ǲ���ʹ������
	static bool IsDirectory(LPCSTR pszDir)   
	{   
		DWORD dwAttr;   
		dwAttr = GetFileAttributes(pszDir);   
		if(dwAttr == -1L) //pszDir��ָĿ�겻����
			return false;  
		if(dwAttr & FILE_ATTRIBUTE_DIRECTORY) //pszDir��ָĿ�����ļ���
			return true;  
		return false;//pszDir��ָĿ�����ļ�
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

		//��׼��ӡ��Ϣ������ʱ��
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
			// �ļ��в�����
			CreateDirectory(CYBER_LOG_FILE_NAME, NULL);
		}

		hFile = fopen(CYBER_LOG_FILE_NAME,"at");
		if(hFile)
		{
			int pos = 0;
			fseek(hFile, 0, SEEK_END);
			pos = ftell( hFile );
			if (pos >= LOG_FILE_SIZE)//��֤����ļ���СΪLOG_FILE_SIZE
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
#define error_f(fmt,...) {error_record_f(fmt,__VA_ARGS__);info_notime_record_f("���ԣ�%s:%d",__FILE__,__LINE__)}
#elif defined CYBER_LOG_HIGH
#define cyber_debug_f(fmt,...){debug_record_f(fmt,__VA_ARGS__)}
#define cyber_log_f(fmt,...) {log_record_f(fmt,__VA_ARGS__)}
#define cyber_log_notime_f(fmt,...) {log_notime_record_f(fmt,__VA_ARGS__)}
#define cyber_error_f(fmt,...) {error_record_f(fmt,__VA_ARGS__);info_notime_record_f("���ԣ�%s:%d",__FILE__,__LINE__)}
#endif

#define xassert(ex) ((ex)?((void)0):info_notime_record_f("%s:\n���ԣ�%s:%d",#ex,__FILE__,__LINE__))

#ifdef __cplusplus
};
#endif // __cplusplus

#endif//End of _CYBER_LOGGER_H
