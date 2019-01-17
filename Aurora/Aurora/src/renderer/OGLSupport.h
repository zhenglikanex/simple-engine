#ifndef OGLSUPPORT_H_
#define OGLSUPPORT_H_

#include <iomanip>

#include "Singleton.h"
#include "glad/glad.h"
#include "LogManager.h"

#define CHECK_GL_ERROR_DEBUG() \
do {\
	GLenum __error = glGetError(); \
	if(__error) { \
		LOG_ERROR() << "OpenGL error " << std::hex << __error << std::dec <<  " in " <<  __FILE__ << " " <<  __FUNCTION__  << " " <<  __LINE__ << LOG_END(); \
	}\
}while(false);

namespace aurora
{
	class OGLSupport : public Singleton<OGLSupport>
	{
	public:
	private:
	};
}

#endif
