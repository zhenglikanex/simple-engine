#ifndef WINDOW_H_
#define WINDOW_H_

#include "Config.h"
#include <windows.h>
#include <windowsx.h>

#include "AuroraDef.h"

namespace aurora {

	class Window
	{
	public:
		Window(const ConfigPtr& config);
		~Window();

		bool Initialize();
		void Destory();

		void SwapBuffers() { ::SwapBuffers(hdc_); }

		operator HWND() { return hwnd_; }

		HDC GetHDC() { return hdc_; }
		uint32_t width() const { return width_; }
		uint32_t height() const { return height_; }
		uint32_t color_bits() const { return color_bits_; }
		uint32_t depth_bits() const { return depth_bits_; }
	private:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		ConfigPtr config_ptr_;
		HWND hwnd_;
		HDC hdc_;
		HGLRC hglrc_;

		uint32_t width_;
		uint32_t height_;
		uint32_t color_bits_;
		uint32_t depth_bits_;
	};
}

#endif
