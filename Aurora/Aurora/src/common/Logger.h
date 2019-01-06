#pragma once

#include <iostream>
#include <string>
#include <memory>

namespace aurora
{
	class Logger
	{
	public:
		enum LoggerTarget
		{
			CONSOLE,
			FILE
		};

	public:
		Logger();
		~Logger();

		Logger(const std::string& file);

		void set_open(bool open) { open_ = open; }
		bool is_open() const { return open_; }

		template<typename T>
		Logger& operator<<(const T& value)
		{
			if (is_open()) {
				////¼ÇÂ¼Ê±¼ä
				//auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				//struct tm tt;
				//localtime_s(&tt, &time);
				//*ostream_ << std::put_time(&tt, "%Y-%m-%d %X") << value;
				*ostream_ << value;
			}
		}
	private:
		LoggerTarget target_;
		std::string file_;
		std::shared_ptr<std::ostream> ostream_;
		bool open_;
	};

	using LoggerPtr = std::shared_ptr<Logger>;
}