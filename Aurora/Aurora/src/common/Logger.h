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

		void Log(const char* message) const;

		void set_open(bool open) { open_ = open; }
		bool is_open() const { return open_; }
	private:
		LoggerTarget target_;
		std::string file_;
		std::shared_ptr<std::ostream> ostream_;
		bool open_;
	};

	using LoggerPtr = std::shared_ptr<Logger>;
}