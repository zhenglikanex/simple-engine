#ifndef RENDER_OBJECT_H_
#define RENDER_OBJECT_H_

#include "AuroraDef.h"
#include "RenderOperation.h"
#include "Material.h"

#include "glm/glm.hpp"

namespace aurora
{
	class RenderObject
	{
	public:
		bool visible_;

		RenderObject(const glm::mat4& model_matrix,const MaterialPtr material,const RenderOperation& render_operation);
		~RenderObject();

		const RenderOperation& GetRenderOperation() const { return render_operation_; }

		void set_material(const MaterialPtr& material) { materail_ = material; }
		const MaterialPtr& material() const { return materail_; }
		
		void set_model_matrix(const glm::mat4& model_matrix) { model_matrix_ = model_matrix; }
		const glm::mat4& model_matrix() const { return model_matrix_; }
	private:
		glm::mat4 model_matrix_;
		MaterialPtr materail_;
		RenderOperation render_operation_;
	};
}

#endif
