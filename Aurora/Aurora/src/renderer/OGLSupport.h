#ifndef OGLSUPPORT_H_
#define OGLSUPPORT_H_

#include "Singleton.h"
#include "glad/glad.h"

//#define CHECK_GL_ERROR_DEBUG() \
//    do { \
//        GLenum __error = glGetError(); \
//        if(__error) { \
//            cocos2d::log("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
//
//        } \
//    } while (false)
//
namespace aurora
{
	class OGLSupport : public Singleton<OGLSupport>
	{
	public:
	private:
	};
}

#endif
