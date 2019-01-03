#include "RenderObject.h"

namespace aurora
{
	RenderObject::RenderObject(const glm::mat4& model_matrix,const MaterialPtr material, const RenderOperation& render_operation)
		:model_matrix_(model_matrix)
		,materail_(material)
		,render_operation_(render_operation)
	{

	}

	RenderObject::~RenderObject()
	{

	}

}

