#ifndef OGLRENDERER_H_
#define OGLRENDERER_H_

#include "AuroraDef.h"
#include "OGLDeviceContext.h"
#include "RenderGroupMap.h"
#include "RenderGroup.h"
#include "RenderQueue.h"
#include "VertexLayout.h"
#include "RenderTexture.h"

#include "glm/glm.hpp"

namespace aurora
{
	class OGLRenderer
	{
	public:
		OGLRenderer(const ConfigPtr& config_ptr);
		~OGLRenderer();

		bool Initialize();
		void Destory();

		void RenderBegin();		// 进行渲染准备
		void Render(const RenderGroupMap& render_group_map);
		void RenderEnd();		// 渲染结束

		void ChangeViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		void set_camrea_position(const glm::vec3& camera_position) { camera_position_ = camera_position; }
		const glm::vec3& camera_position() const { return camera_position_; }

		void set_camera_matrix(const glm::mat4& camera_matrix) { camera_matrix_ = camera_matrix; }
		const glm::mat4& camera_matrix() const { return camera_matrix_; }

		void set_projection_matrix(const glm::mat4& projection_matrix) { projection_matrix_ = projection_matrix; }
		const glm::mat4& projection_matrix() const { return projection_matrix_; }
	private:
		// 渲染阴影贴图
		void RenderShadowPass(const RenderGroupMap& render_group_map);

		void Render(const RenderGroup& render_group);
		void Render(const RenderQueue& render_queue);
		void StartRenderObject(const RenderObject& render_object);
		void DrawRenderOperation(const RenderOperation& render_operation);

		ConfigPtr config_ptr_;
		OGLDeviceContextPtr ogl_device_context_ptr_;

		uint32_t window_width_;
		uint32_t window_height_;

		GLuint vao_;
		GLuint vbo_;	// 顶点缓存
		GLuint ebo_;	// 顶点索引缓存

		glm::vec3 camera_position_;
		glm::mat4 camera_matrix_;
		glm::mat4 projection_matrix_;

		RenderTexturePtr dl_shadow_rt_;		// 方向光的阴影
		RenderTextureCubePtr pl_shadow_rt_;	// 点光源的阴影
		ShaderPtr shader1;
		ShaderPtr shader2;
		TexturePtr texture_;
	};
}

#endif
