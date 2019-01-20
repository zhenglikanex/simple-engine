#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "AuroraDef.h"
#include "Singleton.h"
#include "SceneManager.h"

namespace aurora
{
	class Context :public Singleton<Context>
	{
	public:
		Context();
		~Context();

		bool Initialize();
		void Destory();

		void Update();

		const SceneManagerPtr& scene_manager() const { return scene_manager_; }
	private:
		bool quit_;
		ConfigPtr config_ptr_;
		OGLRendererPtr ogl_renderer_;
		SceneManagerPtr scene_manager_;
	};
}

#endif