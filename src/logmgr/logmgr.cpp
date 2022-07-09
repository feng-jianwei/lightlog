#include <memory>
#include <mutex>
#include "logmgr.h"

using namespace std;

LogMgr *LogMgr::Instance()
{
	static LogMgr logmgr;
	return &logmgr;
}

void LogMgr::AddLog(const std::string &log)
{
	lock_guard<std::mutex> guard(logMutex);
	logs.push(log);	
	variable.notify_one();
}

std::string LogMgr::GetLog()
{
	std::unique_lock<mutex> guard(logMutex);
	while (logs.empty()) {
		variable.wait(guard);
	}
	string log = move(logs.front());
	logs.pop();
	return log;
}

