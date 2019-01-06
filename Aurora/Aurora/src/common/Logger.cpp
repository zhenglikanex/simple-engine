#include "Logger.h"

#include <stdarg.h>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>

namespace aurora {
	Logger::Logger()
		: target_(LoggerTarget::CONSOLE)
		, ostream_(&std::cout, [](void* ptr){})
		, open_(true)
	{

	}

	Logger::~Logger()
	{
		if (target_ == LoggerTarget::FILE) {
			auto ostream = std::dynamic_pointer_cast<std::ofstream>(ostream_);
			ostream->close();
		}
	}

	Logger::Logger(const std::string& file)
		: target_(LoggerTarget::FILE)
		, file_(file)
		, ostream_(std::make_shared<std::ofstream>(std::ofstream(file,std::ios::out)))
		, open_(false)
	{
		auto ostream = std::dynamic_pointer_cast<std::ofstream>(ostream_);
		if (ostream){
			set_open(ostream->is_open());
		}
	}
}