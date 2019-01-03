#include "RenderGroupMap.h"

namespace aurora
{
	RenderGroupMap::RenderGroupMap()
	{
		render_group_map_.insert(std::make_pair(RenderOperation::OperationType::OT_POINT_LIST, RenderGroup()));
		render_group_map_.insert(std::make_pair(RenderOperation::OperationType::OT_LINE_LIST, RenderGroup()));
		render_group_map_.insert(std::make_pair(RenderOperation::OperationType::OT_LINE_STRIP, RenderGroup()));
		render_group_map_.insert(std::make_pair(RenderOperation::OperationType::OT_TRIANGLE_LIST, RenderGroup()));
		render_group_map_.insert(std::make_pair(RenderOperation::OperationType::OT_TRIANGLE_STRIP, RenderGroup()));
		render_group_map_.insert(std::make_pair(RenderOperation::OperationType::OT_TRIANGLE_FAN, RenderGroup()));
	}

	RenderGroupMap::~RenderGroupMap()
	{

	}

	RenderGroupMap::const_iterator RenderGroupMap::begin() const
	{
		return render_group_map_.begin();
	}

	RenderGroupMap::const_iterator RenderGroupMap::end() const
	{
		return render_group_map_.end();
	}

	RenderGroupMap::iterator RenderGroupMap::find(RenderOperation::OperationType type)
	{
		return render_group_map_.find(type);
	}

	void RenderGroupMap::clear()
	{
		for (auto& iter : render_group_map_)
		{
			iter.second.clear();
		}
	}
}