#include "logger/logger.h"
#include "lightlog.h"
#include <thread>
#include <sstream>

using namespace std;
namespace LightLog {
void LightAyncLog(const std::string &log)
{
	stringstream str;
	str << "[T" << std::this_thread::get_id() << ']' << log;
	Logger::Instance()->AddLogs({str.str()});
}

void LightSyncLog(const std::string &log)
{
	stringstream str;
	str << "[T" << std::this_thread::get_id() << ']'<< log;
	Logger::Instance()->DirectWriteLog({str.str()});
}

void OpenAyncLog()
{
	Logger::Instance()->Start();
}

void CloseLog()
{
	Logger::Instance()->Stop();
}
}
