#include "App3D.h"

#include <windows.h>
#include <thread>

#include "Context.h"
#include "Clock.h"

namespace aurora
{
	App3D::App3D()
		:fps_(0)
	{
		set_fps_interval(1.0f / 60.0f);
	}

	App3D::~App3D()
	{
		Destory();
	}

	bool App3D::Create()
	{
		context_ptr_ = Context::GetInstance();
		if (!context_ptr_)
		{
			LOG_ERROR() << "Context Initalized Failed!" << LOG_END();
			return false;
		}

		return OnCreate();
	}

	void App3D::Destory()
	{
		OnDestory();

		if (context_ptr_)
		{
			context_ptr_->Destory();
		}
	}

	void App3D::Update()
	{
		MSG msg;
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// ��������ѭ��
		Context::GetInstance()->Update();

		// ������Ϸ
		OnUpdate();
	}

	void App3D::Run()
	{
		// ��һ֡ʱ������Ϊ����ֵ;
		Global::s_delta_frame_time = fps_interval_;

		while(true)
		{
			Clock begin_clock;

			// ������Ϸ
			Update();
			
			Clock end_clock;

			// ����ǰ֡ʱ�����Ϊ��һ֡ʱ��
			Global::s_delta_frame_time = end_clock - begin_clock;

			// �����ǰ����ʱ��С�����õ�֡�����˯�߳�
			if (Global::s_delta_frame_time < fps_interval_)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>((fps_interval_ - Global::s_delta_frame_time) * 1000)));

				Global::s_delta_frame_time = fps_interval_;
			}

			fps_ = static_cast<int>(std::ceil(1.0f / Global::s_delta_frame_time));
		}
	}
}
