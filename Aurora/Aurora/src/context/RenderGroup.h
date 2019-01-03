#ifndef RENDER_GROUP_H_
#define RENDER_GROUP_H_

#include <map>

#include "RenderQueue.h"

namespace aurora
{
	class RenderGroup
	{
	public:
		//使用map,这里需要依靠key值对RenderQueue进行排序
		using RenderQueueMap = std::map<uint64_t, RenderQueue>;
		using iterator = RenderQueueMap::iterator;
		using const_iterator = RenderQueueMap::const_iterator;
		using InsterResult = RenderQueueMap::_Pairib;

		RenderGroup();
		~RenderGroup();

		iterator find(uint64_t id);
		const_iterator begin() const;
		const_iterator end() const;
		InsterResult inster(uint64_t id, const RenderQueue& render_queue);
		iterator get(const MaterialPtr& material);

		void clear();
	private:
		RenderQueueMap render_queue_map_;
	};
}

#endif
