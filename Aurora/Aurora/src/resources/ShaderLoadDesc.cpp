#include "ShaderLoadDesc.h"
#include "FileHelper.h"
#include "Shader.h"

namespace aurora
{
	ShaderLoadDesc::ShaderLoadDesc(const std::string& vs_file, const std::string& ps_file)
	{
		name_ = vs_file + ps_file;
	}

	ShaderLoadDesc::~ShaderLoadDesc()
	{

	}

	std::shared_ptr<void> ShaderLoadDesc::Create()
	{
		auto vs_path = FileHelper::GetInstance()->GetFullPath(vs_file_);
		auto ps_path = FileHelper::GetInstance()->GetFullPath(ps_file_);

		if (FileHelper::GetInstance()->IsExists(vs_path) && FileHelper::GetInstance()->IsExists(ps_path))
		{
			auto shader = MakeShaderPtr(vs_path.string(), ps_path.string());
			return shader;
		}		
		
		return nullptr;
	}
}