
#ifndef __LIGHT_LOG__
#define __LIGHT_LOG__

#include <cstdio>
#include <string>
#include <utility>

#define LIGHT_EXPORT __attribute__((visibility("default")))

namespace LightLog {
LIGHT_EXPORT void OpenAyncLog();

LIGHT_EXPORT void CloseLog();

LIGHT_EXPORT void LightAyncLog(const std::string &log);

LIGHT_EXPORT void LightSyncLog(const std::string &log);

template <typename... types>
LIGHT_EXPORT void AyncLog(const std::string &formatLog, types&&... args)
{
	char LogStr[300] = {0};
	size_t logSize= snprintf(LogStr, 300, formatLog.c_str(), std::forward<types>(args) ...);
	LightAyncLog(std::string(LogStr));
}

template <typename... types>
LIGHT_EXPORT void SyncLog(const std::string &formatLog, types&& ... args)
{
	char LogStr[300] = {0};
	size_t logSize= snprintf(LogStr, 300, formatLog.c_str(), std::forward<types>(args) ...);
	LightSyncLog(std::string(LogStr));
}
}
#endif
