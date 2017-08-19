#ifndef PATO_CONFIG_H
#define PATO_CONFIG_H

#ifdef __linux__
#ifndef OS_LINUX
#define OS_LINUX
#endif
#else
#define OS_WINDOWS
#endif

#ifndef FORCE_LOW_RES_TEXTURES
#define FORCE_LOW_RES_TEXTURES 1
#endif

#ifndef FORCED_FACTOR
#define FORCED_FACTOR 2
#endif


#ifndef VDEBUG_NO_LIGHT
#define VDEBUG_NO_LIGHT 0
#endif

#ifndef VDEBUG_SIMPLE_COLOR
#define VDEBUG_SIMPLE_COLOR 0
#endif

#if VDEBUG_SIMPLE_COLOR && VDEBUG_NO_LIGHT
#undef VDEBUG_NO_LIGHT
#define VDEBUG_NO_LIGHT 0
#endif

#define D3DX 1
#define OGLES20 2
#define OGLES30 3
#define OGLES31 4
#define OGL 5

#define DRIVER_SELECTED D3DX

#if   DRIVER_SELECTED == OGLES20
	#define USING_OPENGL_ES20
#elif DRIVER_SELECTED == OGLES30
	#define USING_OPENGL_ES30
#elif DRIVER_SELECTED == OGLES31
	#define USING_OPENGL_ES31
#elif DRIVER_SELECTED == D3DX
	#define USING_D3D11
#elif DRIVER_SELECTED == OGL
	#define USING_OPENGL
#else
	#define USING_OPENGL // Default GL
#endif

#if defined(OS_LINUX)
#undef USING_D3D11
#undef USING_OPENGL
#define USING_OPENGL_ES31
#endif

#if defined(USING_OPENGL_ES20) || defined(USING_OPENGL_ES30)  || defined(USING_OPENGL_ES31) || defined(USING_OPENGL)
	#define USING_GL_COMMON
#endif


#define SDL 1
#define FREEGLUT 2

#define WINDOW_MANAGER FREEGLUT

#if WINDOW_MANAGER == SDL
#define USING_SDL
#elif WINDOW_MANAGER == FREEGLUT
#define USING_FREEGLUT
#else
#define USING_SDL
#endif

#ifdef OS_WINDOWS
#undef USING_FREEGLUT
#define USING_SDL
#endif



#endif
