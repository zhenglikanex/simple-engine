#ifndef RESMANAGER_H_
#define RESMANAGER_H_

#include <string>
#include <unordered_map>

#include "Singleton.h"

namespace aurora
{
	template<typename ResLoader>
	class ResManager : public Singleton<ResManager<ResLoader>>
	{
	public:
		bool Initialize() override
		{
			return true;
		}

		using ResType = typename ResLoader::ResType;

		ResType LoadRes(const std::string& name)
		{
			// 寻找是否已经被加载
			auto iter = name_by_res_map_.find(name);
			if (iter != name_by_res_map_.end())
			{
				return iter->second;
			}
			
			ResType res = res_loader_.Load(name);
			if (res)
			{
				name_by_res_map_.insert(std::make_pair(name, res));
			}

			return res;
		}

		void UnLoadRes(const std::string& name)
		{

		}
	private:
		ResLoader res_loader_;
		std::unordered_map<std::string, ResType> name_by_res_map_;
	};
}

#endif
