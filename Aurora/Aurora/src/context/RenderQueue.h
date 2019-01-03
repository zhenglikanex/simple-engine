#ifndef RENDER_QUEUE_H_
#define RENDER_QUEUE_H_

#include <vector>

#include "AuroraDef.h"
#include "RenderObject.h"

namespace aurora
{
	class RenderQueue
	{
	public:
		using RenderQueueType = std::vector<RenderObject>;
		using Iterator = RenderQueueType::iterator;
		using Const_Iterator = RenderQueueType::const_iterator;

		RenderQueue(const MaterialPtr& material);

		Const_Iterator begin() const;
		Const_Iterator end() const;

		void push_back(const RenderObject& render_object);

		void clear();

		const MaterialPtr& materail() const { return material_; }
	private:
		MaterialPtr material_;
		RenderQueueType render_objects_;
	};
}

#endif
