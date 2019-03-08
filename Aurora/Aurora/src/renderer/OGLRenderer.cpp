#include "OGLRenderer.h"

#include <cstddef>

#include "Config.h"
#include "Window.h"
#include "Resources.h"
#include "Material.h"
#include "Shader.h"
#include "LightSystem.h"
#include "RenderTexture.h"
#include "FrameBufferObject.h"
#include "stb_image.h"
#include "Texture.h"

float screen_quad[] =
{
	-1.0f,-1.0f,0.0f, 0.0f,0.0f,
	-1.0f,1.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f,0.0f, 1.0f,1.0f,
	-1.0f,-1.0f,0.0f, 0.0f,0.0f,
	1.0f,1.0f,0.0f, 1.0f,1.0f,
	1.0f,-1.0f,0.0f, 1.0f,0.0f
};

float skybox_vertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

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

		glEnable(GL_DEPTH_TEST);

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		dl_shadow_rt_ = MakeRenderTexturePtr(BaseRenderTexture::TextureFormatType::kRGBA, 8192,8192, 0, true, false);	
		pl_shadow_rt_ = MakeRenderTextureCubePtr(BaseRenderTexture::TextureFormatType::kRGBA, 1024, 1024, 0, true, false);
		hdr_rt_ = MakeRenderTexturePtr(BaseRenderTexture::TextureFormatType::kHalfFloat, window_width_, window_height_,2,true,false);
		hdr_rt_->GetColorTexture(0)->ApplyLinearFilter();
		hdr_rt_->GetColorTexture(1)->ApplyLinearFilter();

		pingpong_blur_rt_[0] = MakeRenderTexturePtr(BaseRenderTexture::TextureFormatType::kHalfFloat, 256, 256, 1, false, false);
		pingpong_blur_rt_[1] = MakeRenderTexturePtr(BaseRenderTexture::TextureFormatType::kHalfFloat, 256, 256, 1, false, false);

		blur_rt_ = MakeRenderTexturePtr(BaseRenderTexture::TextureFormatType::kHalfFloat, window_width_, window_height_, 2, false, false);

		CHECK_GL_ERROR_DEBUG();

		glGenVertexArrays(1, &quad_vao_);
		glGenBuffers(1, &quad_vbo_);

		glBindVertexArray(quad_vao_);

		glBindBuffer(GL_ARRAY_BUFFER, quad_vbo_);
		glBufferData(GL_ARRAY_BUFFER,sizeof(screen_quad), screen_quad, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

		glBindVertexArray(0);

		//
		glGenVertexArrays(1, &sky_vao_);
		glGenBuffers(1, &sky_vbo_);
		
		glBindVertexArray(sky_vao_);

		glBindBuffer(GL_ARRAY_BUFFER, sky_vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), skybox_vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glBindVertexArray(0);

		glGenTextures(1, &tex_depth_);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex_depth_);
		for (int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glGenFramebuffers(1, &fbo_);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tex_depth_, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		shader_ = LoadShader("shader/vs_shadow_map.vs", "shader/fs_shadow_map.fs");
		texture_ = LoadTexture2D("1003.jpg");
		texture_cube_ = LoadTextureCube("ame_bluefreeze/bluefreeze_bk.tga", "ame_bluefreeze/bluefreeze_bk.tga", "ame_bluefreeze/bluefreeze_bk.tga", "ame_bluefreeze/bluefreeze_bk.tga", "ame_bluefreeze/bluefreeze_bk.tga", "ame_bluefreeze/bluefreeze_bk.tga");

		return true;
	}

	void OGLRenderer::Destory()
	{

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

	void OGLRenderer::RenderShadowPass(const RenderGroupMap& render_group_map)
	{
		auto& point_lights = LightSystem::GetInstance()->point_lights();
		auto& directional_lights = LightSystem::GetInstance()->directional_lights();
		auto& spot_lights = LightSystem::GetInstance()->spot_lights();

		//auto shadow_shader = Resources::s_kShadowShader;
		//if (shadow_shader)
		//{
		//	shadow_shader->Bind();

		//	// 方向光阴影
		//	dl_shadow_rt_->fbo()->Bind();
		//	glClear(GL_DEPTH_BUFFER_BIT);

		//	dl_space_matrixs_.clear();

		//	ChangeViewport(0, 0, dl_shadow_rt_->width(), dl_shadow_rt_->height());

		//	for (auto i = 0; i < directional_lights.size(); ++i)
		//	{
		//		auto light = directional_lights[i];
		//		glm::mat4 light_view = glm::lookAt(-light.directional, glm::vec3(0.0f), glm::vec3(0.0,0.0,-1.0));

		//		float near_plane = 1.0f, far_plane = 75.f;
		//		glm::mat4 projection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);

		//		shadow_shader->CommitMat4("light_view", light_view);
		//		shadow_shader->CommitMat4("projection", projection);

		//		dl_space_matrixs_.emplace_back(projection * light_view);

		//		for (auto rgm_iter = render_group_map.begin(); rgm_iter != render_group_map.end(); ++rgm_iter)
		//		{
		//			auto render_group = rgm_iter->second;
		//			for (auto rg_iter = render_group.begin(); rg_iter != render_group.end(); ++rg_iter)
		//			{
		//				auto render_queue = rg_iter->second;
		//				for (auto rq_iter = render_queue.begin(); rq_iter != render_queue.end(); ++rq_iter)
		//				{
		//					auto render_object = *rq_iter;
		//					shadow_shader->CommitMat4("model_matrix", render_object.model_matrix());

		//					DrawRenderOperation(render_object.GetRenderOperation());
		//				}
		//			}
		//		}
		//	}

		//	dl_shadow_rt_->fbo()->UnBind();
		//}

		
		auto point_shadow_shader = Resources::s_kPointShadowShader;
		if (point_shadow_shader)
		{
			point_shadow_shader->Bind();
			
			std::array<glm::mat4, 6> shadow_matrices;

			// 点光源阴影
			pl_shadow_rt_->fbo()->Bind();
			//glEnable(GL_DEPTH_TEST);
			//glDepthMask(GL_LESS);
			glClear(GL_DEPTH_BUFFER_BIT);

			ChangeViewport(0, 0, pl_shadow_rt_->width(), pl_shadow_rt_->height());

			for (uint32_t i = 0; i < point_lights.size(); ++i)
			{
				auto light = point_lights[i];
				float near_plane = 1.0f;
				float far_plane = 75.0f;
				glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)pl_shadow_rt_->width() / (float)pl_shadow_rt_->height(), near_plane, far_plane);
				shadow_matrices[0] = projection * glm::lookAt(light.position, light.position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
				shadow_matrices[1] = projection * glm::lookAt(light.position, light.position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
				shadow_matrices[2] = projection * glm::lookAt(light.position, light.position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
				shadow_matrices[3] = projection * glm::lookAt(light.position, light.position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0,-1.0));
				shadow_matrices[4] = projection * glm::lookAt(light.position, light.position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0));
				shadow_matrices[5] = projection * glm::lookAt(light.position, light.position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0));

				for (uint32_t j = 0; j < 6; ++j)
				{
					point_shadow_shader->CommitMat4("shadow_matrices[" + std::to_string(j) + "]", shadow_matrices[j]);
				}
				point_shadow_shader->CommitFloat("far_plane", far_plane);
				point_shadow_shader->CommitVec3("light_pos", light.position);
				
				for (auto rgm_iter = render_group_map.begin(); rgm_iter != render_group_map.end(); ++rgm_iter)
				{
					auto render_group = rgm_iter->second;
					for (auto rg_iter = render_group.begin(); rg_iter != render_group.end(); ++rg_iter)
					{
						auto render_queue = rg_iter->second;
						for (auto rq_iter = render_queue.begin(); rq_iter != render_queue.end(); ++rq_iter)
						{
							auto render_object = *rq_iter;
							point_shadow_shader->CommitMat4("model_matrix", render_object.model_matrix());
							
							DrawRenderOperation(render_object.GetRenderOperation());
						}
					}
				}
			}

			pl_shadow_rt_->fbo()->UnBind();
		}
	}

	void OGLRenderer::Render(const RenderGroupMap& render_group_map)
	{
		RenderShadowPass(render_group_map);

		if (hdr_rt_)
		{
			ChangeViewport(0, 0, hdr_rt_->width(), hdr_rt_->height());

			hdr_rt_->fbo()->Bind();

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto iter = render_group_map.begin(); iter != render_group_map.end(); ++iter)
			{
				Render(iter->second);
			}
			hdr_rt_->fbo()->UnBind();

			PostProcessing();
		}
		else 
		{
			ChangeViewport(0, 0,window_width_,window_height_);
			for (auto iter = render_group_map.begin(); iter != render_group_map.end(); ++iter)
			{
				Render(iter->second);
			}
		}

		//RenderSkyBox();
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
			//if (iter->visible_)
			{
				StartRenderObject(*iter);
			}
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

			shader->CommitInt("dir_light_count", directional_lights.size());

			for (auto i = 0; i < directional_lights.size(); ++i)
			{
				char position_name[256];
				sprintf_s(position_name, "directional_lights[%d].directional", i);
				shader->CommitVec3(position_name, directional_lights[i].directional);

				char color_name[256];
				sprintf_s(color_name, "directional_lights[%d].color", i);
				shader->CommitVec3(color_name, directional_lights[i].color);

				char intensity_name[256];
				sprintf_s(intensity_name, "directional_lights[%d].intensity", i);
				shader->CommitFloat(intensity_name, directional_lights[i].intensity);
			}

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

			// 
			auto tex_dl_shadow = dl_shadow_rt_->depth_texture();
			if (tex_dl_shadow)
			{
				tex_dl_shadow->Bind(5);		//TODO：应该给每个贴图类型指定通道,比如阴影贴图应该有固定的通道,这样才不会占用
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
				GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
				shader->CommitInt("tex_dl_shadow", 5);
			}

			auto tex_pl_shadow = pl_shadow_rt_->depth_texture();
			if (tex_pl_shadow)
			{
				tex_pl_shadow->Bind(6);
				shader->CommitInt("tex_pl_shadow", 6);
			}

			for (uint32_t i = 0; i < dl_space_matrixs_.size(); ++i)
			{
				char name[256];
				sprintf_s(name, "dl_space_matrixs[%d]", i);
				shader->CommitMat4(name, dl_space_matrixs_[i]);
			}

			shader->CommitFloat("far_plane", 75.0f);

			// 提交顶点数据
			DrawRenderOperation(render_object.GetRenderOperation());
		}
		
		material->UnBind();
	}

	void OGLRenderer::DrawRenderOperation(const RenderOperation& render_operation)
	{
		auto& vao = render_operation.vao();

		CHECK_GL_ERROR_DEBUG();

		//绑定缓存
		glBindVertexArray(vao->id());

		// 提交渲染
		if (vao->index_buffer()->index_layout() == IndexLayout::k32Bit)
		{
			glDrawElements(GL_TRIANGLES, vao->index_buffer()->index_count(), GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawElements(GL_TRIANGLES, vao->index_buffer()->index_count(), GL_UNSIGNED_SHORT, 0);
		}
		

		// 取消绑定
		glBindVertexArray(0);
	}

	void OGLRenderer::RenderSkyBox()
	{
		auto shader = Resources::s_kSkyBoxShader;
		if (shader)
		{

			shader->Bind();
			// 
			glDepthFunc(GL_LEQUAL);

			glBindVertexArray(sky_vao_);

			pl_shadow_rt_->depth_texture()->Bind(0);
			//pl_shadow_rt_->GetColorTexture(0)->Bind(0);
			//glBindTexture(GL_TEXTURE_CUBE_MAP, tex_depth_);
			//texture_cube_->Bind(0);

			shader->CommitInt("tex_skybox",0);

			// 提交Camera矩阵
			shader->CommitMat4("camera_matrix", glm::mat4(glm::mat3(camera_matrix_)));

			// 提交投影矩阵
			shader->CommitMat4("proj_matrix", projection_matrix_);

			glDrawArrays(GL_TRIANGLES, 0, sizeof(skybox_vertices) / sizeof(float));

			glDepthFunc(GL_LESS);

			shader->UnBind();
		}
	}

	void OGLRenderer::PostProcessing()
	{
		CHECK_GL_ERROR_DEBUG();
		if(hdr_rt_)
		{
			auto blur_shader = Resources::s_kBlurShader;
			blur_shader->Bind();

			bool horizontal = false;
			bool first = true;
			// blur处理
			for (int i = 0; i < 10; ++i)
			{
				auto rt = horizontal ? pingpong_blur_rt_[0] : pingpong_blur_rt_[1];
				auto prev_rt = horizontal ? pingpong_blur_rt_[1] : pingpong_blur_rt_[0];

				rt->fbo()->Bind();
				ChangeViewport(0, 0, rt->width(), rt->height());
				glClear(GL_COLOR_BUFFER_BIT);

				blur_shader->CommitBool("horizontal", horizontal);
				blur_shader->CommitInt("tex", 0);

				if (first)
				{
					hdr_rt_->GetColorTexture(1)->Bind(0);
				}
				else
				{
					prev_rt->GetColorTexture(0)->Bind(0);
				}

				glBindVertexArray(quad_vao_);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				
				horizontal = !horizontal;
				if (first)
				{
					first = false;
				}
			}
			//glBindFramebuffer(GL_FRAMEBUFFER,0);

			// 将blur后的纹理添加到hdr上
			hdr_rt_->fbo()->Bind();
			ChangeViewport(0, 0, hdr_rt_->width(), hdr_rt_->height());
			if (horizontal)
			{
				pingpong_blur_rt_[0]->GetColorTexture(0)->Bind(0);
			}
			else
			{
				pingpong_blur_rt_[1]->GetColorTexture(0)->Bind(0);
			}
			
			hdr_rt_->GetColorTexture(0)->Bind(1);

			auto bloom_shader = Resources::s_kBloomShader;
			bloom_shader->Bind();
			bloom_shader->CommitInt("tex_bloom", 0);
			bloom_shader->CommitInt("tex_hdr", 1);

			glBindVertexArray(quad_vao_);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			hdr_rt_->fbo()->UnBind();

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			ChangeViewport(0,0,window_width_, window_height_);

			//auto hdr_shader = Resources::s_kToneMappingHdrShader;
			auto hdr_shader = Resources::s_kExposureHdr;
			if (hdr_shader)
			{
				hdr_shader->Bind();

				glBindVertexArray(quad_vao_);

				hdr_rt_->GetColorTexture(0)->Bind(0);
				hdr_shader->CommitInt("tex_hdr", 0);
				hdr_shader->CommitFloat("exposure", 1);

				glDrawArrays(GL_TRIANGLES, 0, 6);

				hdr_shader->UnBind();
			}
		}
	}
}