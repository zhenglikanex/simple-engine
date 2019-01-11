#include "MaterialLoadDesc.h"

namespace aurora
{
	MaterialLoadDesc::MaterialLoadDesc(const std::string& name)
	{
		name_ = name;
	}

	MaterialLoadDesc::~MaterialLoadDesc()
	{

	}

	std::shared_ptr<void> MaterialLoadDesc::Create()
	{
		if (name_.substr(name_.find_last_of('.') + 1, name_.size()) != "mtl")
		{
			return nullptr;
		}

		

		return nullptr;
	}
}