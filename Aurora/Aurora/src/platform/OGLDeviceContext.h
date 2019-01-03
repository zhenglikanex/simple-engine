#ifndef OGL_DEVICE_CONTEXT_H_
#define OGL_DEVICE_CONTEXT_H_

#include "AuroraDef.h"
#include "IDeviceRenderContext.h"
#include "glad/glad.h"

namespace aurora
{
	class OGLDeviceContext : public IDeviceRenderContext
	{
	public:
		OGLDeviceContext(const ConfigPtr& config_ptr);
		~OGLDeviceContext();

		bool Initialize() override;
		bool Destory() override;

		void StartRender() override;
		void SwapBuffers() override;

		void MakeThreadContext() override;

		void ResizeBackBuffer(int width, int height) override;

		const WindowPtr& window_ptr() const { return window_ptr_; }
	private:
		ConfigPtr config_ptr_;
		WindowPtr window_ptr_;
	};
}

#endif
