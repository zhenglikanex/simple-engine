#include "ShaderLoadDesc.h"
#include "FileHelper.h"
#include "Shader.h"

namespace aurora
{
	ShaderLoadDesc::ShaderLoadDesc(const std::string& vs_file, const std::string& fs_file)
		:vs_file_(vs_file),fs_file_(fs_file)
	{
		name_ = vs_file + fs_file;
	}

	ShaderLoadDesc::ShaderLoadDesc(const std::string& vs_file, const std::string& gs_file, const std::string& fs_file)
		:vs_file_(vs_file),gs_file_(gs_file),fs_file_(fs_file)
	{
		name_ = vs_file_ + gs_file_ + fs_file_;
	}

	ShaderLoadDesc::~ShaderLoadDesc()
	{

	}

	std::shared_ptr<void> ShaderLoadDesc::Create()
	{
		filesystem::path empty_path;
		auto vs_path = FileHelper::GetInstance()->GetFullPath(vs_file_);
		if (vs_path == empty_path)
		{
			LOG_INFO() << "Shader加载错误: " << vs_file_ << "文件不存在！" << LOG_END();

			return nullptr;
		}

		auto fs_path = FileHelper::GetInstance()->GetFullPath(fs_file_);
		if (fs_path == empty_path)
		{
			LOG_INFO() << "Shader加载错误: " << fs_file_ << "文件不存在！" << LOG_END();

			return nullptr;
		}

		if (gs_file_ == "")
		{
			return MakeShaderPtr(vs_path.string(), fs_path.string());
		}
		else 
		{
			auto gs_path = FileHelper::GetInstance()->GetFullPath(gs_file_);
			if (gs_path == empty_path)
			{
				LOG_INFO() << "Shader加载错误: " << gs_file_ << "文件不存在！" << LOG_END();

				return nullptr;
			}
			return MakeShaderPtr(vs_path.string(), gs_path.string(), fs_path.string());
		}
		
		return nullptr;
	}
}