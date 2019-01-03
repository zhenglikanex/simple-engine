#include "FileHelper.h"
#include <windows.h>
#include <fstream>

namespace aurora
{
	FileHelper::FileHelper()
	{
	}

	FileHelper::~FileHelper()
	{

	}

	bool FileHelper::Initialize()
	{
		current_path_ = filesystem::current_path();

		search_paths_.push_back(current_path_);

		return true;
	}

	void FileHelper::AddSearchPath(const std::string& path)
	{
		auto full_path = current_path_ / path;
		for (auto& entry : search_paths_)
		{
			if (entry == full_path)
			{
				return;
			}
		}

		search_paths_.push_back(full_path);
	}

	filesystem::path FileHelper::GetFullPath(const std::string& file_name)
	{
		// 判断是否已经是完整的路径
		if (IsExists(file_name))
		{
			return filesystem::path(file_name);
		}

		for (auto& entry : search_paths_)
		{
			filesystem::path path = entry / file_name;
			if (IsExists(path))
			{
				return path;
			}
		}

		// 返回个空的路径
		filesystem::path path;
		return path;
	}

	std::shared_ptr<std::ifstream> FileHelper::OpenFile(const std::string& file_name, uint32_t mode /* = std::ios_base::in */)
	{
		auto full_path = GetFullPath(file_name);
		if (full_path.empty())
		{
			return std::shared_ptr<std::ifstream>();
		}

		std::shared_ptr<std::ifstream> istream = std::make_shared<std::ifstream>(full_path.string(), mode);
		return istream;
	}

	FileIdentifer FileHelper::OpenFileIdentifer(const std::string& file_name, uint32_t mode /* = std::ios_base::in */)
	{
		return FileIdentifer(file_name, OpenFile(file_name, mode));
	}

	bool FileHelper::IsExists(const std::string& file_name)
	{
		return filesystem::exists(file_name);
	}
	
	bool FileHelper::IsExists(const filesystem::path& path)
	{
		return filesystem::exists(path);
	}
}