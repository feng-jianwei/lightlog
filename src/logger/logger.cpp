#include <atomic>
#include <string>
#include <thread>
#include <vector>
#include "logger.h"
#include "sys/stat.h"

using namespace std;
Logger *Logger::Instance()
{
	static Logger logger;
	return &logger;
}

void Logger::Start()
{
	worker = thread([this] {
					while (!isExit) {
						DirectWriteLog(GetLogs());
					}
				}
			);
}

void Logger::DirectWriteLog(const vector<std::string> &vecLogs)
{
	std::lock_guard<std::mutex> guard(fileMutex);
	if (fileName.empty() || !CheckLogFileSize()) {
		NewLogFile();	
	}	
	fileStream.open(fileName, ios::app|ios::out);
	for (const auto &log : vecLogs) {
		fileStream << log << '\n';
	}
	fileStream.close();
	fileStream.clear();
}

void Logger::AddLogs(const vector<string> &vecLogs)
{
	std::unique_lock guard(logMutex);
	for (const auto &log : vecLogs) {
		logs.push_back(log);
	}	
	cond.notify_one();
}

std::vector<std::string> Logger::GetLogs()
{
	std::vector<string> tmp;
	std::unique_lock guard(logMutex);
	while (logs.empty()) {
		cond.wait(guard);
	}
	logs.swap(tmp);
	return move(tmp);
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
	fileName.clear();
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
