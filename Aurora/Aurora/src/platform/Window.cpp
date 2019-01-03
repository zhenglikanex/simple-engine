#include "Window.h"

#include <tchar.h>

#include "StringUtil.h"

namespace aurora
{

	Window::Window(const ConfigPtr& config)
		: config_ptr_(config)
		, hwnd_(0)
		, hdc_(0)
		, hglrc_(0)
	{
	}

	Window::~Window() {}

	bool Window::Initialize()
	{
		std::wstring class_name = _T("Aurora");

		HINSTANCE hInstace = GetModuleHandle(NULL);
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstace;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = class_name.c_str();

		RegisterClassEx(&wc);

		std::wstring titile = StringUtil::String2WString(config_ptr_->GetValue("title").GetString());
		width_ = config_ptr_->GetValue("width").GetInt();
		height_ = config_ptr_->GetValue("height").GetInt();
		color_bits_ = config_ptr_->GetValue("color_bits").GetInt();
		depth_bits_ = config_ptr_->GetValue("depth_bits").GetInt();

		HWND hWnd = CreateWindowEx(0,
			class_name.c_str(),
			titile.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width_,
			height_,
			NULL,
			NULL,
			hInstace,
			this);

		ShowWindow(hWnd, SW_SHOW);

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = color_bits_;
		pfd.cDepthBits = depth_bits_;
		pfd.iLayerType = PFD_MAIN_PLANE;

		HDC hDC = GetDC(hWnd);

		int nPixelFormat = ChoosePixelFormat(hDC, &pfd);
		if (nPixelFormat == 0) return false;

		int result = SetPixelFormat(hDC, nPixelFormat, &pfd);
		if (result != 1) {
			return false;
		}

		// ����glRenderContext;
		HGLRC glrc = wglCreateContext(hDC);
		if (!glrc)
		{
			return false;
		}

		// ��glRenderContext;
		if (!wglMakeCurrent(hDC, glrc))
		{
			return false;
		}

		hwnd_ = hWnd;
		hdc_ = hDC;
		hglrc_ = glrc;

		return true;
	}

	void Window::Destory()
	{
		if (hwnd_ != 0)											/**< ���ھ���Ƿ���� */
		{
			if (hdc_ != 0)
			{
				// ���glRenderContext��;
				wglMakeCurrent(hdc_, 0);

				ReleaseDC(hwnd_, hdc_);							/**< �ͷŴ��ڵ��豸������ */
				hdc_ = 0;
			}
			DestroyWindow(hwnd_);								/**< ɾ������ */
			hwnd_ = 0;											/**< ���ô��ھ��Ϊ0 */
		}
	}

	LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window* pThis;
		if (message == WM_NCCREATE)
		{
			SetLastError(0);
			if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, NULL))
			{
				if (GetLastError() != 0)
					return FALSE;
			}
		}
		else
		{
		}

		// sort through and find what code to run for the message given
		switch (message)
		{
		case WM_PAINT:
		{
			
		}
		break;

		case WM_KEYDOWN:
		{

		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		}

		// Handle any messages the switch statement didn't
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}