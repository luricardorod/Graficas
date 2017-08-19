#ifndef PATO_UTILS_GL_H
#define PATO_UTILS_GL_H

#include "../Config.h"

#include <stdio.h>
#include <iostream>
#include <string>

#if defined(USING_OPENGL_ES20)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(USING_OPENGL_ES30)
#include <GLES3/gl3.h>
#elif defined(USING_OPENGL_ES31)
#include <GLES3/gl31.h>
#elif defined(USING_OPENGL)
#ifdef OS_WINDOWS
#include <GL/glew.h>
#elif defined(OS_LINUX)
#include <GL/gl.h>
#endif
#endif

#ifdef USING_GL_COMMON
void checkcompilederrors(GLuint shader, GLenum type);
void CheckGLError();
void CheckFBStatus();
GLuint createShader(GLenum type, char* pSource);
#else
void checkcompilederrors(unsigned int shader, unsigned int type);
unsigned int createShader(unsigned int type, char* pSource);
#endif

char *file2string(const char *path);
char * file2string(const char *path, long & fileSz);
std::string RemovePath(std::string p);

const std::string dummyShaderVS = "cbuffer ConstantBuffer { float4x4 WVP; float4x4 World; float4 CameraPos; float4 LightPos; float4 LightCol; float4 LightOri; float4 LightInt; float4 Ambient; } struct VS_INPUT { float4 Vertex : POSITION; }; struct VS_OUTPUT { float4 hPosition : SV_POSITION; }; VS_OUTPUT VS(VS_INPUT input) { VS_OUTPUT OUT; OUT.hPosition = mul(WVP , input.Vertex); return OUT; }";
const std::string dummyShaderFS = "cbuffer ConstantBuffer { float4x4 WVP; float4x4 World; float4 CameraPos; float4 LightPos; float4 LightCol; float4 LightOri; float4 LightInt; float4 Ambient; } struct VS_OUTPUT { float4 hPosition : SV_POSITION; }; float4 FS(VS_OUTPUT input) : SV_TARGET { return float4(1.0, 0.0, 1.0, 1.0); }";

#endif