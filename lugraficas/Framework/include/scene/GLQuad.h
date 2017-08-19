#ifndef PATO_QUAD_GL_H
#define PATO_QUAD_GL_H

#include "../Config.h"
#ifdef USING_OPENGL_ES20
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <video/GLTexture.h>
#elif defined(USING_OPENGL_ES30)
#include <GLES3/gl3.h>
#include <video/GLTexture.h>
#elif defined(USING_OPENGL_ES31)
#include <GLES3/gl31.h>
#include <video/GLTexture.h>
#elif defined(USING_OPENGL)
#include <GL/glew.h>
#include <video/GLTexture.h>
#endif

#include <video/BaseDriver.h>
#include <CMatrix4D.h>
#include <scene/PrimitiveBase.h>

class GLQuad : public PrimitiveBase
{
public:
	struct Vert
	{
		float x,y,z,w;
		float u,v;
	};

	GLQuad(){}
	void Create();
	void Create(char *){}
	void Transform(CMatrix4D * t);
	void Draw(CMatrix4D * t, CMatrix4D * vp);
	void Destroy();

	unsigned int	SigBase;

	Vert			vertices[4];
	unsigned short	indices[6];
	unsigned int	VB;
	unsigned int	IB;
	CMatrix4D		transform;
	CVector4D		LightPositions[128];
	CVector4D		LightColors[128];

};

#endif