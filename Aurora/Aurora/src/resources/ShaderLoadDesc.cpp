#include "ShaderLoadDesc.h"
#include "FileHelper.h"

namespace aurora
{
	ShaderLoadDesc::ShaderLoadDesc(const std::string& vs_file, const std::string& ps_file)
	{
		vs_path_ = FileHelper::GetInstance()->GetFullPath(vs_file);
		ps_path_ = FileHelper::GetInstance()->GetFullPath(ps_file);

		if (FileHelper::GetInstance()->IsExists(vs_path_) && FileHelper::GetInstance()->IsExists(ps_path_))
		{
			name_ = vs_path_.string() + ps_path_.string();
		}
	}

	ShaderLoadDesc::~ShaderLoadDesc()
	{

	}

	std::shared_ptr<void> ShaderLoadDesc::Create()
	{
		if (name_ == "")
		{
			return 
		}
	}
}