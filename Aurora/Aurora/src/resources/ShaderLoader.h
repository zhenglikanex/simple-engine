#ifndef SHADER_LOADER_H_
#define SHADER_LOADER_H_

#include <string>
#include <fstream>

#include "AuroraDef.h"
#include "ResLoader.h"
#include "ResManager.h"

#define LOAD_SHADER(name) ShaderManager::GetInstance()->LoadRes(name);

namespace aurora
{
	class ShaderLoader : public ResLoader<ShaderPtr>
	{
	public:
		~ShaderLoader()
		{

		}

		ShaderPtr Load(const std::string& name) override;
	private:
		std::string directory_;
	};

	class ShaderManager : public ResManager<ShaderLoader>
	{
	public:
		//一些通用的shader
		static ShaderPtr s_kSimpleShader;
		static ShaderPtr s_kNoramlShader;
		static ShaderPtr s_kDiffuseShader;
		static ShaderPtr s_kSpecularShader;
		static ShaderPtr s_kNoramlDiffuseShader;
		static ShaderPtr s_kNoramlSpecularShader;
		static ShaderPtr s_kDiffuseSpecularShader;
		static ShaderPtr s_kNormalDiffuseSpecularShader;

		static std::shared_ptr<ShaderManager> GetInstance()
		{
			if (instance_)
			{
				return instance_;
			}

			instance_ = std::make_shared<ShaderManager>();
			instance_->Initialize();
			
			return instance_;
		}

		bool Initialize() override;
	private:
		static std::shared_ptr<ShaderManager> instance_;
	};
}


#endif
