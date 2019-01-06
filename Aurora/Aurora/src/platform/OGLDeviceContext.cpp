#include "OGLDeviceContext.h"

#include "Config.h"
#include "Window.h"

namespace aurora
{
	OGLDeviceContext::OGLDeviceContext(const ConfigPtr& config_ptr)
		:config_ptr_(config_ptr)
	{
		
	}

	OGLDeviceContext::~OGLDeviceContext()
	{
		
	}

	bool OGLDeviceContext::Initialize()
	{
		window_ptr_ = MakeWindowPtr(config_ptr_);
		if (window_ptr_ && window_ptr_->Initialize())
		{

		}
		else
		{
			LOG_ERROR() << "Window Create Failed !" << LOG_END();
			return false;
		}

		if (!gladLoadGL())
		{
			LOG_ERROR() << "glad Load Failed !" << LOG_END();
			return false;
		}

		return true;
	}

	bool OGLDeviceContext::Destory()
	{
		return true;
	}

	void OGLDeviceContext::StartRender()
	{

	}

	void OGLDeviceContext::SwapBuffers()
	{
		if (window_ptr_)
		{
			window_ptr_->SwapBuffers();
		}
	}

	void OGLDeviceContext::MakeThreadContext()
	{

	}

	void OGLDeviceContext::ResizeBackBuffer(int width, int height)
	{

	}
}