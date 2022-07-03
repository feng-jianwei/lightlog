#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <type_traits>

class LogMgr {
public:
	static LogMgr *Instance();
	void AddLog(const std::string &log);
	std::string GetLog();

private:
	LogMgr() = default;
	std::queue<std::string> logs;
	std::mutex logMutex;
	std::condition_variable variable;
};
