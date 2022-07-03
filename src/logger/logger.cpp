#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sys/fcntl.h>
#include <thread>
#include "logger.h"
#include "logmgr/logmgr.h"
#include "sys/stat.h"

using namespace std;
Logger *Logger::Instance()
{
	static Logger logger;
	return &logger;
}

void Logger::Start()
{
	thread t([this] {
				while (true) {
					DirectWriteLog(LogMgr::Instance()->GetLog());
				}
			}
		);
	t.detach();
}

void Logger::DirectWriteLog(const std::string &log)
{
	std::lock_guard<std::mutex> guard(fileMutex);
	if (fileName.empty() || !CheckLogFileSize()) {
		NewLogFile();	
	}	
	fileStream.open(fileName, ios::app|ios::out);
	fileStream << log << '\n';
	fileStream.close();
	fileStream.clear();
}

bool Logger::CheckLogFileSize()
{
	struct stat buf;	
	return stat(fileName.c_str(), &buf) == 0 && buf.st_size < fileSize;
}

void Logger::SetLogPath(const std::string &logPath)
{
	this->logPath = logPath;	
}

void Logger::NewLogFile()
{
	if (logPath.empty()) {
		char *pwd = getenv("PWD");
		fileName.append(pwd ? "" : string(pwd));
	} else {
		fileName.append(logPath);
	}
	time_t t;
	time(&t);
	struct tm *timeLocal = localtime(&t);
	char logTime[100] = {0};
	strftime(logTime, 100, "%Y%m%d%H%M%S", timeLocal);
	string logName("lightlog_");
	logName.append(string(logTime));
	fileName.append(logName);
}
