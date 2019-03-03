#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <unordered_map>

#include "AuroraDef.h"
#include "Singleton.h"
#include "ResLoadDesc.h"

namespace aurora
{
	class Resources : public Singleton<Resources>
	{
	public:
		static MaterialPtr s_kSimpleMtl;
		static MaterialPtr s_kNoramlMtl;
		static MaterialPtr s_kDiffuseMtl;
		static MaterialPtr s_kSpecularMtl;
		static MaterialPtr s_kNoramlDiffuseMtl;
		static MaterialPtr s_kNoramlSpecularMtl;
		static MaterialPtr s_kDiffuseSpecularMtl;
		static MaterialPtr s_kNormalDiffuseSpecularMtl;

		static ShaderPtr s_kShadowShader;
		static ShaderPtr s_kPointShadowShader;

		static ShaderPtr s_kSkyBoxShader;
	public:
		using NameByResourceMap = std::unordered_map<std::string, std::shared_ptr<void>>;

		void CreateDefaultMaterial();
		void CreateDefaultShader();

		std::shared_ptr<void> FindResource(const std::string& name);

		template<typename ResType>
		std::shared_ptr<ResType> LoadResource(ResLoadDesc& res_load_desc)
		{
			auto resource = FindResource(res_load_desc.name());
			if (resource)
			{
				return std::static_pointer_cast<ResType>(resource);
			}
			
			resource = res_load_desc.Create();
			if (resource)
			{
				name_by_resource_map_.emplace(res_load_desc.name(), resource);
				return std::static_pointer_cast<ResType>(resource);
			}

			return nullptr;
		}
	private:
		NameByResourceMap name_by_resource_map_;
	};

	//各种资源加载函数(不用模板实现,如果用模板实现的话用到的地方必须包含资源的ResLoadDesc头文件,不可取)
	Texture2DPtr LoadTexture2D(const std::string& name);
	TextureCubePtr LoadTextureCube(const std::string& top,const std::string& bottom,const std::string& left,const std::string& right,const std::string& front,const std::string& back);
	TextureCubePtr LoadTextureCube(const std::string& floder, const std::string& ext);
	ShaderPtr LoadShader(const std::string& vs_file, const std::string& ps_file);
	ShaderPtr LoadShader(const std::string& vs_file, const std::string& gs_file, const std::string& ps_file);
	MaterialPtr LoadMaterial(const std::string& name);
	MeshPtr LoadMesh(const std::string& name);
}

#endif
