#include "RenderQueue.h"

namespace aurora
{
	RenderQueue::RenderQueue(const MaterialPtr& material)
		:material_(material)
	{

	}

	RenderQueue::Const_Iterator RenderQueue::begin() const
	{
		return render_objects_.begin();
	}

	RenderQueue::Const_Iterator RenderQueue::end() const
	{
		return render_objects_.end();
	}

	void RenderQueue::push_back(const RenderObject& render_object)
	{
		return render_objects_.push_back(render_object);
	}

	void RenderQueue::clear()
	{
		render_objects_.clear();
	}
}