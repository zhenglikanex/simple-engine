#include "Context.h"
#include "Resources.h"
#include "Config.h"
#include "OGLRenderer.h"
#include "Camera.h"

namespace aurora
{
	Context::Context()
	{
		// 加载引擎默认配置;
		config_ptr_ = MakeConfigPtr("aurora.config");
	}

	Context::~Context()
	{

	}

	bool Context::Initialize()
	{
		ogl_renderer_ = MakeOGLRendererPtr(config_ptr_);
		if(!ogl_renderer_ || !ogl_renderer_->Initialize())
		{
			LOG_ERROR() << "OGLRenderer Initalize failed!" << LOG_END();
			return false;
		}

		// 创建默认资源
		Resources::GetInstance()->CreateDefaultMaterial();

		return true;
	}

	void Context::Destory()
	{

	}

	void Context::Update()
	{
		if (ogl_renderer_)
		{
			// 进行场景更新
			scene_manager_.Update();

			ogl_renderer_->RenderBegin();

			// 根据camra进行渲染
			for (auto& camera : scene_manager_.cameras())
			{
				ogl_renderer_->set_camrea_position(camera->GetComponent<SceneNode>()->position());
				ogl_renderer_->set_camera_matrix(camera->GetCameraMatrix());
				ogl_renderer_->set_projection_matrix(camera->GetProjectionMatrix());
				ogl_renderer_->Render(camera->render_group_map());

				camera->render_group_map().clear();
			}

			ogl_renderer_->RenderEnd();
		}
	}
}