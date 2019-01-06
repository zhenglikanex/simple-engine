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
		using NameByResourceMap = std::unordered_map<std::string, std::shared_ptr<void>>;

		std::shared_ptr<void> FindResource(const std::string& name);

		template<typename ResType>
		auto LoadResource(const ResLoadDesc& res_load_desc)
		{
			auto resource = FindResource(res_load_desc.name());
			if (resource)
			{
				return std::static_pointer_cast<ResType>(resource);
			}
			
			resource = res_load_desc.Create();
			if (resource)
			{
				name_by_resource_map_.insert(res_load_desc.name(), resource);
				return std::static_pointer_cast<ResType>(resource);
			}

			return nullptr;
		}
	private:
		NameByResourceMap name_by_resource_map_;
	};

	//������Դ���غ���(����ģ��ʵ��,�����ģ��ʵ�ֵĻ��õ��ĵط����������Դ��ResLoadDescͷ�ļ�,����ȡ)
	Texture2DPtr LoadTexture2D(const std::string& name);

	TextureCubePtr LoadTextureCube(const std::string& top,
		const std::string& bottom,
		const std::string& left,
		const std::string& right,
		const std::string& front,
		const std::string& back);
	TextureCubePtr LoadTextureCube(const std::string& floder, const std::string& ext);
}

#endif