#ifndef PATO_GLDRIVER_H
#define PATO_GLDRIVER_H

#include "../Config.h"

#include <video/BaseDriver.h>

#ifdef OS_WINDOWS
#if defined(USING_OPENGL_ES20)
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(USING_OPENGL_ES30)
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#elif defined(USING_OPENGL_ES31)
#include <EGL/egl.h>
#include <GLES3/gl31.h>
#elif defined(USING_OPENGL)
#include <GL/glew.h>
#include <SDL/SDL.h>
#else
#include <GL/glew.h>
#include <SDL/SDL.h>
#endif
#elif defined(OS_LINUX)
#if defined(USING_OPENGL_ES20)
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(USING_OPENGL_ES30)
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#elif defined(USING_OPENGL_ES31)
#include <EGL/egl.h>
#include <GLES3/gl31.h>
#elif defined(USING_OPENGL)
#include <GL/glew.h>
#else
#include <GL/glew.h>
#endif
#endif

class GLDriver : public BaseDriver
{
public:
	GLDriver() { }
	void	InitDriver();
	void	CreateSurfaces();
	void	DestroySurfaces();
	void	Update();
	void	DestroyDriver();
	void	SetWindow(void *window) ;
	void	SetDimensions(int, int);

	int 	 CreateTexture(std::string path);
	Texture* GetTexture(int id);
	void	 DestroyTexture();

	int 	CreateRT(int nrt, int cf, int df, int w, int h);
	void	PushRT(int id);
	void	PopRT();
	void	DestroyRT(int id);
	void	DestroyRTs();

	int			CreateShader(std::string src_vs, std::string src_fs, unsigned int sig);
	ShaderBase*	GetShaderSig(unsigned int sig);
	ShaderBase*	GetShaderIdx(int Id);
	void		DestroyShaders();

	void	Clear();
	void	SwapBuffers();
	bool	CheckExtension(std::string s);
#if defined(USING_OPENGL_ES20) || defined(USING_OPENGL_ES30) || defined(USING_OPENGL_ES31)
	EGLDisplay			eglDisplay;
	EGLConfig			eglConfig;
	EGLSurface			eglSurface;
	EGLContext			eglContext;

	EGLNativeWindowType	eglWindow;
#endif
	GLint				CurrentFBO;
#if defined(USING_OPENGL) || defined(USING_OPENGL_ES30) || defined(USING_OPENGL_ES31)
	GLenum				DrawBuffers[16];
#endif

	int	width, height;
	std::vector<std::string>	ExtensionsTok;
	std::string					Extensions;

};

#endif