#include "OGLRenderer.h"

#include <cstddef>

#include "Config.h"
#include "Window.h"
#include "Material.h"
#include "Shader.h"
#include "LightSystem.h"

namespace aurora
{
	static std::unordered_map<RenderOperation::OperationType, GLenum> s_OperationTypeByDrawEnumMap =
	{
		{RenderOperation::OperationType::OT_LINE_LIST,GL_LINES},
		{RenderOperation::OperationType::OT_LINE_STRIP,GL_LINE_STRIP},
		{RenderOperation::OperationType::OT_POINT_LIST,GL_POINTS},
		{RenderOperation::OperationType::OT_TRIANGLE_FAN,GL_TRIANGLE_FAN},
		{RenderOperation::OperationType::OT_TRIANGLE_LIST,GL_TRIANGLES},
		{RenderOperation::OperationType::OT_TRIANGLE_STRIP,GL_TRIANGLE_STRIP}
	};

	OGLRenderer::OGLRenderer(const ConfigPtr& config_ptr)
		:config_ptr_(config_ptr)
		, window_width_(0)
		, window_height_(0)
	{

	}

	OGLRenderer::~OGLRenderer()
	{

	}

	bool OGLRenderer::Initialize()
	{
		ogl_device_context_ptr_ = MakeOGLDeviceContextPtr(config_ptr_);
		if (!ogl_device_context_ptr_ || !ogl_device_context_ptr_->Initialize())
		{

		}

		window_width_ = ogl_device_context_ptr_->window_ptr()->width();
		window_height_ = ogl_device_context_ptr_->window_ptr()->height();

		ChangeViewport(0, 0, window_width_, window_height_);

		glGenVertexArrays(1, &vao_);
		glGenBuffers(1, &vbo_);
		glGenBuffers(1, &ebo_);

		glEnable(GL_DEPTH_TEST);

		return true;
	}

	void OGLRenderer::Destory()
	{
		glDeleteVertexArrays(1, &vao_);
		glDeleteBuffers(1, &vbo_);
		glDeleteBuffers(1, &ebo_);
	}

	// 进行渲染准备
	void OGLRenderer::RenderBegin()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// 渲染结束
	void OGLRenderer::RenderEnd()
	{
		ogl_device_context_ptr_->SwapBuffers();
	}

	void OGLRenderer::ChangeViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OGLRenderer::Render(const RenderGroupMap& render_group_map)
	{

		for (auto iter = render_group_map.begin(); iter != render_group_map.end(); ++iter)
		{
			Render(iter->second);
		}
	}

	void OGLRenderer::Render(const RenderGroup& render_group)
	{
		for (auto iter = render_group.begin(); iter != render_group.end(); ++iter)
		{
			Render(iter->second);
		}
	}

	void OGLRenderer::Render(const RenderQueue& render_queue)
	{
		//auto material = render_queue.materail();
		for (auto iter = render_queue.begin(); iter != render_queue.end(); ++iter)
		{
			StartRenderObject(*iter);
		}
	}

	void OGLRenderer::StartRenderObject(const RenderObject& render_object)
	{
		auto material = render_object.material();
		material->Bind();

		auto shader = material->shader_ptr();
		if (shader)
		{
			shader->CommitVec3("camera_position", camera_position_);
			
			// 提交模型矩阵
			shader->CommitMat4("model_matrix", render_object.model_matrix());

			// 提交Camera矩阵
			shader->CommitMat4("camera_matrix", camera_matrix_);

			// 提交投影矩阵
			shader->CommitMat4("proj_matrix", projection_matrix_);

			// 提交灯光数据
			auto& point_lights = LightSystem::GetInstance()->point_lights();
			auto& directional_lights = LightSystem::GetInstance()->directional_lights();
			auto& spot_lights = LightSystem::GetInstance()->spot_lights();

			for (auto i = 0; i < point_lights.size(); ++i)
			{
				char position_name[256];
				sprintf_s(position_name, "point_lights[%d].position", i);
				shader->CommitVec3(position_name, point_lights[i].position);

				char color_name[256];
				sprintf_s(color_name, "point_lights[%d].color", i);
				shader->CommitVec3(color_name, point_lights[i].color);

				char intensity_name[256];
				sprintf_s(intensity_name, "point_lights[%d].intensity", i);
				shader->CommitFloat(intensity_name, point_lights[i].intensity);

				char radius_name[256];
				sprintf_s(radius_name, "point_lights[%d].radius", i);
				shader->CommitFloat(radius_name, point_lights[i].radius);

				char constant_name[256];
				sprintf_s(constant_name, "point_lights[%d].constant", i);
				shader->CommitFloat(constant_name, point_lights[i].constant);

				char linear_name[256];
				sprintf_s(linear_name, "point_lights[%d].linear", i);
				shader->CommitFloat(linear_name, point_lights[i].linear);

				char quadratic_name[256];
				sprintf_s(quadratic_name, "point_lights[%d].quadratic", i);
				shader->CommitFloat(quadratic_name, point_lights[i].quadratic);
			}

			// 提交顶点数据
			DrawRenderOperation(render_object.GetRenderOperation());
		}
		
		material->UnBind();
	}

	void OGLRenderer::DrawRenderOperation(const RenderOperation& render_operation)
	{
		auto& vertex_buffer = render_operation.vertex_buffer();
		auto& index_buffer = render_operation.index_buffer();

		//绑定缓存
		glBindVertexArray(vao_);

		// 上传vertex_buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer.id());
		//glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size(), vertex_buffer.GetRawData(), GL_STREAM_DRAW);

		// 上传index_buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.id());
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer.size(), index_buffer.GetRawData(), GL_STREAM_DRAW);

		// 绑定顶点属性
		switch (vertex_buffer.vertex_layout())
		{
		case VertexLayout::kP3FN3FT2F:
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2F, position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2F, normal));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2F, texcoords));
			break;
		case VertexLayout::kP3FN3FT2FT3FB3F:
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer.vertex_layout()), 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, normal));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, texcoords));
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, tangent));
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, bitangent));
		default:
			break;
		}

		// 提交渲染
		glDrawElements(GL_TRIANGLES,render_operation.index_buffer().size(), GL_UNSIGNED_INT, 0);

		// 取消绑定
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}