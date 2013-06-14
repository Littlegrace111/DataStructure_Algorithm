#ifndef _HANDLE_EXCEPTION_H
#define _HANDLE_EXCEPTION_H
#include <string>

#ifdef _DEBUG
#ifndef MYTRACE
#define MYTRACE(fmt, ...) printf("[Log]:%s\n", fmt);
#define MYERROR_TRACE(fmt, ...) printf("[ERR]:%s\n", fmt);
#endif
#else
#ifndef MYTRACE
#define MYTRACE
#endif
#endif

class MyException{
public:
	MyException(
		std::string error_info = "",
		int errorId = 0
	): m_errorId(errorId), m_ErrorInfo(error_info)
	{
		//MYTRACE("MyException is called");
	}

	MyException(MyException& myExp)
		: m_errorId(myExp.GetErrorId()),
		  m_ErrorInfo(myExp.GetErrorInfo())
	{
		//MYTRACE("MyException copy constructor is called");
	}

	~MyException()
	{
		//MYTRACE("MyException destructor is called");
	}

	int GetErrorId()const { return m_errorId; }
	std::string& GetErrorInfo() { return m_ErrorInfo; }
	std::string  GetErrorInfo()const { return m_ErrorInfo; }

public:
	int m_errorId;
	std::string m_ErrorInfo;
};

#endif