#include "Config.h"

#include <fstream>
#include <sstream>
#include <string>

#include "FileHelper.h"

namespace aurora
{
	Config::Config(const std::string& config_name)
		:config_name_(config_name),is_valid_(false)
	{
		LoadConfig(config_name_);
	}

	Config::~Config()
	{

	}

	void Config::LoadConfig(const std::string& config_name)
	{
		if (is_valid_)
		{
			return;
		}

		config_name_ = config_name;

		auto file_identifer = FileHelper::GetInstance()->OpenFileIdentifer(config_name_);
		if (file_identifer)
		{
			document_ptr_ = std::make_shared<rapidjson::Document>();
			document_ptr_->Parse(file_identifer.string().c_str());
			is_valid_ = true;
		}
	}

	Config::Value& Config::GetValue(const std::string& name)
	{
		return (*document_ptr_)[name.c_str()];
	}

	void Config::Save()
	{
		//TODO:
		/*rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document_.Accept(writer);*/
	}

	Config::Value& Config::operator[](const std::string& name)
	{
		return GetValue(name);
	}
}