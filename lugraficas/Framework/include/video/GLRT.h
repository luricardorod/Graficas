#ifndef PATO_GLESXRT_H
#define PATO_GLESXRT_H

#include "../Config.h"

#include <video/BaseDriver.h>
#include <vector>

#if defined(USING_OPENGL_ES20)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(USING_OPENGL_ES30)
#include <GLES3/gl3.h>
#elif defined(USING_OPENGL_ES31)
#include <GLES3/gl31.h>
#elif defined(USING_OPENGL)
#include <GL/glew.h>
#else
#include <GL/glew.h>
#ifdef USING_SDL
#include <SDL/SDL.h>
#endif
#endif

class GLRT : public BaseRT
{
public:
    virtual ~GLRT() {}
	bool	LoadAPIRT();
	void	DestroyAPIRT();

	std::vector<GLuint>		vFrameBuffers;
	std::vector<GLuint>		vGLColorTex;
	GLuint					DepthTexture;
};

#endif