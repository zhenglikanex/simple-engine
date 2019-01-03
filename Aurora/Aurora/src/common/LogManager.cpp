#include "LogManager.h"

#include <cstdarg>
#include "Logger.h"

namespace aurora
{
	Log<LogManager::LogLevel::kINFO> LogManager::s_info_log;
	Log<LogManager::LogLevel::kWARNING> LogManager::s_warning_log;
	Log<LogManager::LogLevel::kDEBUG> LogManager::s_debug_log;
	Log<LogManager::LogLevel::kERROR> LogManager::s_error_log;
	Log<LogManager::LogLevel::kTRACE> LogManager::s_trace_log;

	bool LogManager::Initialize()
	{
		auto logger = std::make_shared<Logger>();
		AddLogger("defulat", logger);

		return true;
	}

	void LogManager::AddLogger(const std::string& name, const LoggerPtr& logger)
	{
		logger_map_.insert(std::make_pair(name, logger));
	}

	LogManager::LoggerMapItr LogManager::GetLoggerByName(const std::string& name)
	{
		return logger_map_.find(name);
	}

	void LogManager::Log(LogLevel log_level, const char* msg) const
	{
		switch (log_level)
		{
		case LogManager::kERROR:
			LogError(msg);
			break;

		case LogManager::kWARNING:
			LogWarning(msg);
			break;

		case LogManager::kINFO:
			LogInfo(msg);
			break;

		case LogManager::kDEBUG:
			LogDebug(msg);
			break;

		case LogManager::kTRACE:
			LogTrace(msg);
			break;

		default:
			break;
		}
	}

	void LogManager::Log(const char* message) const
	{
		for (auto iter : logger_map_) {
			iter.second->Log(message);
		}
	}

	void LogManager::LogError(const char* message) const
	{
		char buf[1024] = "[Error] ";
		strcat_s(buf, message);
		Log(buf);
	}

	void LogManager::LogWarning(const char* message) const
	{
		char buf[1024] = "[Warning] ";
		strcat_s(buf, message);
		Log(buf);
	}

	void LogManager::LogInfo(const char* message) const
	{
		char buf[1024] = "[Info] ";
		strcat_s(buf, message);
		Log(buf);
	}

	void LogManager::LogDebug(const char* message) const
	{
		char buf[1024] = "[Debug] ";
		strcat_s(buf, message);
		Log(buf);
	}

	void LogManager::LogTrace(const char* message) const
	{
		char buf[1024] = "[Trace] ";
		strcat_s(buf, message);
		Log(buf);
	}
}