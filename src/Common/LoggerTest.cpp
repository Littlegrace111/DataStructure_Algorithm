#include <stdio.h>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

#pragma comment(lib, "log4cxx.lib")

using namespace std;
using namespace log4cxx;
using namespace log4cxx::helpers;

int main(int argc, char* argv)
{
	//����log4cxx�������ļ�������ʹ�������ļ�
	//PropertyConfigurator::configure("log4cxx.properties");

	LoggerPtr logger(Logger::getLogger("MyApp"));

	try{
		BasicConfigurator::configure();
		LOG4CXX_INFO(logger, "hello");
		LOG4CXX_DEBUG(logger, "world");

		int x = 0;
		for(x; x<100; x++)
		{
			//LOG4CXX_INFO();
		}
	}catch(exception&){

	}



	////���һ��logger������ʹ��RootLogger
	//LoggerPtr rootLogger = Logger::getRootLogger();

	////����һ��INFO������������
	//LOG4CXX_INFO(rootLogger, "it works!");

	getchar();
	return 0;
}