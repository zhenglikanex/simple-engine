#ifndef RES_LOADER_H_
#define RES_LOADER_H_

namespace aurora
{
	template<typename Res>
	class ResLoader
	{
	public:
		using ResType = Res;

		virtual ~ResLoader() = 0
		{

		}

		virtual ResType Load(const std::string& name) = 0;
	};
}

#endif
