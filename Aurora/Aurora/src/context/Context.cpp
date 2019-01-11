#include "Context.h"
#include "Resources.h"
#include "Config.h"
#include "OGLRenderer.h"
#include "Camera.h"

namespace aurora
{
	Context::Context()
	{
		// ��������Ĭ������;
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

		// ����Ĭ����Դ
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
			// ���г�������
			scene_manager_.Update();

			ogl_renderer_->RenderBegin();

			// ����camra������Ⱦ
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