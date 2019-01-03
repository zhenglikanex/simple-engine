#include "ShaderLoader.h"
#include "FileHelper.h"
#include "Config.h"
#include "Shader.h"

namespace aurora
{
	ShaderPtr ShaderLoader::Load(const std::string& name)
	{
		directory_ = name.substr(0, name.find_first_of('/'));

		auto config = Config(name);
		if (!config.IsValid())
		{
			return ShaderPtr();
		}

		// TODO:不够健壮,暂时不管,后面要做脚本解析类
		std::string vs_file  = directory_ + "/" + config["vs_file"].GetString();
		std::string fs_file = directory_ + "/" + config["fs_file"].GetString();

		auto shader_ptr = MakeShaderPtr(name,vs_file, fs_file);
		return shader_ptr;
	}

	/************************************************************************/
	ShaderPtr ShaderManager::s_kSimpleShader = nullptr;
	ShaderPtr ShaderManager::s_kNoramlShader = nullptr;
	ShaderPtr ShaderManager::s_kDiffuseShader = nullptr;
	ShaderPtr ShaderManager::s_kSpecularShader = nullptr;
	ShaderPtr ShaderManager::s_kNoramlDiffuseShader = nullptr;
	ShaderPtr ShaderManager::s_kNoramlSpecularShader = nullptr;
	ShaderPtr ShaderManager::s_kDiffuseSpecularShader = nullptr;
	ShaderPtr ShaderManager::s_kNormalDiffuseSpecularShader = nullptr;

	std::shared_ptr<ShaderManager> ShaderManager::instance_ = nullptr;

	bool ShaderManager::Initialize()
	{
		s_kSimpleShader = LOAD_SHADER("shader/simple_shader.effect");
		s_kNoramlShader = LOAD_SHADER("shader/simple_shader.effect");
		s_kDiffuseShader = LOAD_SHADER("shader/simple_shader.effect");
		s_kSpecularShader = LOAD_SHADER("shader/simple_shader.effect");
		s_kNoramlDiffuseShader = LOAD_SHADER("shader/simple_shader.effect");
		s_kNoramlSpecularShader = LOAD_SHADER("shader/simple_shader.effect");
		s_kDiffuseSpecularShader = LOAD_SHADER("shader/simple_shader.effect");
		s_kNormalDiffuseSpecularShader = LOAD_SHADER("shader/simple_shader.effect");
		return true;
	}
}