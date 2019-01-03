#ifndef RENDER_GROUP_MAP_H_
#define RENDER_GROUP_MAP_H_

#include <unordered_map>

#include "RenderOperation.h"
#include "RenderGroup.h"

namespace aurora
{
	// 根据RenderOperator的OperatorType包含多个RenderGroup
	// RenderGroupMap属于一个Camera
	class RenderGroupMap
	{
	public:
		using RenderGroupMMP = std::unordered_map<RenderOperation::OperationType, RenderGroup>;
		using iterator = RenderGroupMMP::iterator;
		using const_iterator = RenderGroupMMP::const_iterator;

		RenderGroupMap();
		~RenderGroupMap();

		const_iterator begin() const;
		const_iterator end() const;

		iterator find(RenderOperation::OperationType type);

		void clear();
	private:
		RenderGroupMMP render_group_map_;
	};
}

#endif
