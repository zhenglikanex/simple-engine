#ifndef MATERIAL_LOAD_DESC_H_
#define MATERIAL_LOAD_DESC_H_

#include "ResLoadDesc.h"

namespace aurora
{
	class MaterialLoadDesc : public ResLoadDesc
	{
	public:
		MaterialLoadDesc(const std::string& name);
		virtual ~MaterialLoadDesc();

		std::shared_ptr<void> Create() override;
	private:
	};
}

#endif
