#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include "IComponent.h"
#include "RenderOperation.h"
#include "AuroraDef.h"
#include "AABB.h"

namespace aurora
{
	// ��Ⱦ����Ļ���
	class IRenderer : public IComponent
	{
	public:
		IRenderer() : layer_id_(s_DefautltLayer) { }
		virtual ~IRenderer() = 0 {}

		void set_layer_id(uint32_t layer_id) { layer_id_ = layer_id; }
		uint32_t layer_id() const { return layer_id_; }

		virtual const AABB& GetBoundingBox() const = 0;
	protected:
		uint32_t layer_id_;		// ͨ��layer_id��camera����,�����ᱻ�ĸ��������Ⱦ
		AABB boundingbox_;
	};
}

#endif