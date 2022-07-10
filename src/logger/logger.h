#include <condition_variable>
#include <fstream>
#include <string>
#include <mutex>
#include <vector>
#include <thread>
#include <atomic>

class Logger {
public:
	static Logger *Instance();
	void DirectWriteLog(const std::vector<std::string> &log);
	void AddLogs(const std::vector<std::string> &vecLogs);
	std::vector<std::string> GetLogs();
	void SetLogPath(const std::string &logPath);
	bool CheckLogFileSize();
	void NewLogFile();
	void Start();	

private:
	Logger() = default;
	~Logger()
	{
		isExit = true;
		worker.join();
	}
	off_t fileSize {20 * 1024};
	std::string fileName;
	std::string logPath;
	std::vector<std::string> logs;
	std::ofstream fileStream;
	std::mutex fileMutex;
	std::mutex logMutex;
	std::condition_variable cond;
	std::thread worker;
	std::atomic<bool> isExit{false};
};
