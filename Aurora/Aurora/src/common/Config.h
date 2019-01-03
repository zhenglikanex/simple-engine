#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <unordered_map>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace aurora
{
	class Config
	{
	public:
		typedef rapidjson::Value Value;

		Config(const std::string& config_name);
		~Config();

		void LoadConfig(const std::string& config_name);
		
		bool IsValid() const { return is_valid_; }

		Value& GetValue(const std::string& name);

		void Save();

		Value& operator[](const std::string& name);
	private:
		std::string config_name_;
		std::shared_ptr<rapidjson::Document> document_ptr_;
		bool is_valid_;
	};
}

#endif
