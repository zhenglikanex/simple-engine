#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_

#include <iostream>
#include <stdint.h>
#include <unordered_map>
#include <string>
#include <memory>

#include "Singleton.h"

#include "Logger.h"

namespace aurora
{	
	template<int LevelType>
	class Log;

	class LogManager : public Singleton<LogManager>
	{
	public:
		enum LogLevel
		{
			kINFO,
			kWARNING,
			kDEBUG,
			kERROR,
			kTRACE,
		};

		typedef std::unordered_map<std::string, LoggerPtr> LoggerMap;
		typedef LoggerMap::iterator LoggerMapItr;

	public:
		static Log<LogLevel::kINFO> s_info_log;
		static Log<LogLevel::kWARNING> s_warning_log;
		static Log<LogLevel::kDEBUG> s_debug_log;
		static Log<LogLevel::kERROR> s_error_log;
		static Log<LogLevel::kTRACE> s_trace_log;

	public:
		bool Initialize() override;
		void AddLogger(const std::string& name,const LoggerPtr& logger);
		LoggerMapItr GetLoggerByName(const std::string& name);
		
		void Log(LogLevel log_level, const char* msg) const;

		void Log(const char* message) const;
		void LogError(const char* message) const;
		void LogWarning(const char* meesage) const;
		void LogInfo(const char* message) const;
		void LogDebug(const char* message) const;
		void LogTrace(const char* message) const;
	private:
		LoggerMap logger_map_;

	};

	template<int LevelType>
	class Log
	{
	public:
		void operator<<(const std::string& msg)
		{
			LogManager::GetInstance()->Log((LogManager::LogLevel)LevelType, msg.c_str());
		}
	};
}

#endif