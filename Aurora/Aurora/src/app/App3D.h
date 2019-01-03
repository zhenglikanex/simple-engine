#ifndef APP3D_H_
#define APP3D_H_

#include "AuroraDef.h"

namespace aurora
{
	class App3D
	{
	public:
		App3D();
		virtual ~App3D() = 0;

		bool Create();
		void Destory();
		void Update();

		void Run();

		void set_fps_interval(float fps_interval) { fps_interval_ = fps_interval; }
		float fps_interval() { return fps_interval_; }

		int fps() { return fps_; }
	protected:
		virtual bool OnCreate() = 0;
		virtual void OnDestory() = 0;
		virtual void OnUpdate() = 0;
	private:
		ContextPtr context_ptr_;
		float fps_interval_;
		int fps_;
	};
}

#endif
