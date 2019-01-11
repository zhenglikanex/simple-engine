#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

#include "Singleton.h"

#define LOG_END() LogManager::s_log_end
#define LOG() LogManager::GetInstance()->Log()
#define LOG_INFO() LOG() << "[INFO]"
#define LOG_ERROR() LOG() << "[ERROR]"
#define LOG_DEBUG() LOG() << "[DEBUG]"
#define LOG_WARNING() LOG() << "[WARNING]"
#define LOG_TRACE() LOG() << "[TARCE]"

namespace aurora
{	
	struct LogEnd
	{
		friend std::ostream& operator<<(std::ostream& os, LogEnd);
	};

	inline std::ostream& operator<<(std::ostream& os, LogEnd)
	{
		os << std::endl;
		return os;
	}

	class LogManager : public Singleton<LogManager>
	{
	public:
		static LogEnd s_log_end;

		bool Initialize() override;
		void AddLogger(const std::string& file);

		template<typename T>
		LogManager& operator<<(const T& value)
		{
			std::cout << value;
			
			for (auto& logger : file_logger_map_)
			{
				*logger.second << value;
			}

			return *this;
		}

		LogManager& Log();
	private:
		std::unordered_map<std::string, std::shared_ptr<std::ofstream>> file_logger_map_;
	};
}

#endif