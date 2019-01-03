#include "RenderGroup.h"
#include "Material.h"

namespace aurora
{
	RenderGroup::RenderGroup()
	{

	}

	RenderGroup::~RenderGroup()
	{

	}

	RenderGroup::iterator RenderGroup::find(uint64_t id)
	{
		return render_queue_map_.find(id);
	}

	RenderGroup::const_iterator RenderGroup::begin() const
	{
		return render_queue_map_.begin();
	}

	RenderGroup::const_iterator RenderGroup::end() const
	{
		return render_queue_map_.end();
	}

	RenderGroup::InsterResult RenderGroup::inster(uint64_t id, const RenderQueue& render_queue)
	{
		return render_queue_map_.insert(std::make_pair(id, render_queue));
	}

	RenderGroup::iterator RenderGroup::get(const MaterialPtr& material)
	{
		auto id = material->GetMaterialId();

		auto iter = find(id);
		if (iter == end())
		{
			auto result = inster(id, RenderQueue(material));
			return result.first;
		}

		return iter;
	}

	void RenderGroup::clear()
	{
		render_queue_map_.clear();
	}
}