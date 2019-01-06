#include "Resources.h"
#include "TextureLoadDesc.h"

namespace aurora
{
	std::shared_ptr<void> Resources::FindResource(const std::string& name)
	{
		auto iter = name_by_resource_map_.find(name);
		if (iter != name_by_resource_map_.end())
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
}