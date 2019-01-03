#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include "IComponent.h"
#include "RenderOperation.h"
#include "AuroraDef.h"
#include "AABB.h"

namespace aurora
{
	// 渲染组件的基类
	class IRenderer : public IComponent
	{
	public:
		IRenderer() : layer_id_(s_DefautltLayer) { }
		virtual ~IRenderer() = 0 {}

		void set_layer_id(uint32_t layer_id) { layer_id_ = layer_id; }
		uint32_t layer_id() const { return layer_id_; }

		virtual const AABB& GetBoundingBox() const = 0;
	protected:
		uint32_t layer_id_;		// 通过layer_id与camera关联,决定会被哪个摄像机渲染
		AABB boundingbox_;
	};
}

#endif