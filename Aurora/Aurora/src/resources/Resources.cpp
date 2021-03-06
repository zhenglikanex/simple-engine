#include "Resources.h"
#include "Material.h"
#include "TextureLoadDesc.h"
#include "ShaderLoadDesc.h"
#include "MeshLoadDesc.h"
#include "MaterialLoadDesc.h"

namespace aurora
{
	MaterialPtr Resources::s_kSimpleMtl = nullptr;
	MaterialPtr Resources::s_kNoramlMtl = nullptr;
	MaterialPtr Resources::s_kDiffuseMtl = nullptr;
	MaterialPtr Resources::s_kSpecularMtl = nullptr;
	MaterialPtr Resources::s_kNoramlDiffuseMtl = nullptr;
	MaterialPtr Resources::s_kNoramlSpecularMtl = nullptr;
	MaterialPtr Resources::s_kDiffuseSpecularMtl = nullptr;
	MaterialPtr Resources::s_kNormalDiffuseSpecularMtl = nullptr;

	ShaderPtr Resources::s_kShadowShader = nullptr;
	ShaderPtr Resources::s_kPointShadowShader = nullptr;
	ShaderPtr Resources::s_kSkyBoxShader = nullptr;
	ShaderPtr Resources::s_kToneMappingHdrShader = nullptr;
	ShaderPtr Resources::s_kExposureHdr = nullptr;
	ShaderPtr Resources::s_kBlurShader = nullptr;
	ShaderPtr Resources::s_kBloomShader = nullptr;

	void Resources::CreateDefaultMaterial()
	{
		auto simple_shader = LoadShader("shader/vs_simple_shader.vs", "shader/fs_simple_shader.fs");
		Resources::s_kSimpleMtl = MakeMaterialPtr(simple_shader);

		/*Resources::s_kNoramlMtl = MakeMaterialPtr(simple_shader);
		Resources::s_kDiffuseMtl = MakeMaterialPtr(simple_shader);
		Resources::s_kSpecularMtl = MakeMaterialPtr(simple_shader);
		Resources::s_kNoramlDiffuseMtl = MakeMaterialPtr(simple_shader);
		Resources::s_kNoramlSpecularMtl = MakeMaterialPtr(simple_shader);
		Resources::s_kDiffuseSpecularMtl = MakeMaterialPtr(simple_shader);
		Resources::s_kNormalDiffuseSpecularMtl = MakeMaterialPtr(simple_shader);*/
	}

	void Resources::CreateDefaultShader()
	{
		Resources::s_kShadowShader = LoadShader("shader/vs_shadow.vs", "shader/fs_shadow.fs");
		Resources::s_kPointShadowShader = LoadShader("shader/vs_point_light_shadow.vs", "shader/gs_point_light_shadow.gs", "shader/fs_point_light_shadow.fs");
		Resources::s_kSkyBoxShader = LoadShader("shader/vs_skybox.vs", "shader/fs_skybox.fs");
		Resources::s_kToneMappingHdrShader = LoadShader("shader/tone_mapping_hdr.vs", "shader/tone_mapping_hdr.fs");
		Resources::s_kExposureHdr = LoadShader("shader/exposure_hdr.vs","shader/exposure_hdr.fs");
		Resources::s_kBlurShader = LoadShader("shader/blur.vs", "shader/blur.fs");
		Resources::s_kBloomShader = LoadShader("shader/bloom.vs", "shader/bloom.fs");
	}

	std::shared_ptr<void> Resources::FindResource(const std::string& name)
	{
		auto iter = name_by_resource_map_.find(name);
		if (iter == name_by_resource_map_.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	Texture2DPtr LoadTexture2D(const std::string& name)
	{
		auto res_load_desc = Texture2DLoadDesc(name);
		return std::static_pointer_cast<Texture2D>(Resources::GetInstance()->LoadResource<Texture2D>(res_load_desc));
	}

	TextureCubePtr LoadTextureCube(const std::string& top,
		const std::string& bottom,
		const std::string& left,
		const std::string& right,
		const std::string& front,
		const std::string& back)
	{
		auto res_load_desc = TextureCubeLoadDesc(top, bottom, left, right, front, back);
		return std::static_pointer_cast<TextureCube>(Resources::GetInstance()->LoadResource<TextureCube>(res_load_desc));
	}

	TextureCubePtr LoadTextureCube(const std::string& floder, const std::string& ext)
	{
		auto res_load_desc = TextureCubeLoadDesc(floder, ext);
		return std::static_pointer_cast<TextureCube>(Resources::GetInstance()->LoadResource<TextureCube>(res_load_desc));
	}

	ShaderPtr LoadShader(const std::string& vs_file, const std::string& ps_file)
	{
		auto res_load_desc = ShaderLoadDesc(vs_file, ps_file);
		return std::static_pointer_cast<Shader>(Resources::GetInstance()->LoadResource<Shader>(res_load_desc));
	}

	ShaderPtr LoadShader(const std::string& vs_file, const std::string& gs_file, const std::string& ps_file)
	{
		auto res_load_desc = ShaderLoadDesc(vs_file,gs_file,ps_file);
		return std::static_pointer_cast<Shader>(Resources::GetInstance()->LoadResource<Shader>(res_load_desc));
	}

	MaterialPtr LoadMaterial(const std::string& name)
	{
		return nullptr;
	}

	MeshPtr LoadMesh(const std::string& name)
	{
		auto res_load_desc = MeshLoadDesc(name);
		return std::static_pointer_cast<Mesh>(Resources::GetInstance()->LoadResource<Mesh>(res_load_desc));
	}
}