#include "LogManager.h"

namespace aurora
{
	LogEnd LogManager::s_log_end;

	bool LogManager::Initialize()
	{

		return true;
	}

	void LogManager::AddLogger(const std::string& file)
	{
		auto iter = file_logger_map_.find(file);
		if (iter != file_logger_map_.end())
		{
			return;
		}

		auto logger = std::make_shared <std::ofstream>(file);
		if (logger)
		{
			file_logger_map_.insert(std::make_pair(file, logger));
		}
	}

	LogManager& LogManager::Log()
	{
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		struct tm tt;
		localtime_s(&tt, &time);
		*this << std::put_time(&tt, "%Y-%m-%d %X");

		return *this;
	}
}