#ifndef IDEVICECONTEXT_H_
#define IDEVICECONTEXT_H_

namespace aurora
{
	class IDeviceRenderContext
	{
	public:
		virtual ~IDeviceRenderContext() = 0 { }

		virtual bool Initialize() = 0;
		virtual bool Destory() = 0;

		virtual void StartRender() = 0;
		virtual void SwapBuffers() = 0;

		virtual void MakeThreadContext() = 0;

		virtual void ResizeBackBuffer(int width, int height) = 0;
	private:
	};
}

#endif