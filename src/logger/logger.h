#include <fstream>
#include <string>
#include <mutex>
class Logger {
public:
	static Logger *Instance();
	void DirectWriteLog(const std::string &log);
	void SetLogPath(const std::string& logPath);
	bool CheckLogFileSize();
	void NewLogFile();
	void Start();	
private:
	Logger() = default;
	off_t fileSize {20 * 1024};
	std::string fileName;
	std::string logPath;
	std::ofstream fileStream;
	std::mutex fileMutex;
};
