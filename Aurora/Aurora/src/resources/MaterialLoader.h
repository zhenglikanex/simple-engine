#ifndef MATERIAL_LOADER_H_
#define MATERIAL_LOADER_H_

#include "AuroraDef.h"
#include "ResLoader.h"
#include "ResManager.h"

namespace aurora
{
	class MaterialLoader : public ResLoader<MaterialPtr>
	{
	public:
		~MaterialLoader()
		{

		}

		MaterialPtr Load(const std::string& name) override;
	};

	using MaterialManager = ResManager<MaterialLoader>;
}

#endif
