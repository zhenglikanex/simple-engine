#ifndef FILE_HELPER_H_
#define FILE_HELPER_H_

#include <string>
// C++17(¾ÍÊÇboostµÄfilesystem)
#include <experimental/filesystem>

#include "AuroraDef.h"
#include "FileIdentifer.h"

using namespace std::experimental;

namespace aurora
{
	class FileHelper : public Singleton<FileHelper>
	{
	public:
		FileHelper();
		~FileHelper();

		bool Initialize() override; 

		void AddSearchPath(const std::string& path);

		filesystem::path GetFullPath(const std::string& file_name);

		std::shared_ptr<std::ifstream> OpenFile(const std::string& file_name, uint32_t mode = std::ios_base::in);
		FileIdentifer OpenFileIdentifer(const std::string& file_name, uint32_t mode = std::ios_base::in);

		bool IsExists(const std::string& file_name);
		bool IsExists(const filesystem::path& path);

		const filesystem::path& current_path() const { return current_path_; }
	private:
		filesystem::path current_path_;
		std::vector<filesystem::path> search_paths_;
	};
}

#endif
