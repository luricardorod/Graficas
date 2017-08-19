#ifndef PATO_TRIANGLEGL_H
#define PATO_TRIANGLEGL_H

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
#elif defined(USING_D3D11)
#include <video/D3DXTexture.h>
#include <D3Dcompiler.h>
#endif

#include <CMatrix4D.h>
#include <utils/Utils.h>

#include <scene/PrimitiveBase.h>



//#define USE_ARRAY_OF_STRUCTS
#define USE_VBO

#ifdef USE_VBO
struct triVertex
{
	float x, y, z;
	float r, g, b;
};
#else
	#ifdef USE_ARRAY_OF_STRUCTS
	struct triVertex
	{
		float x,y,z;
		float r,g,b;
	};
	#else
	struct triVertex
	{
		float x, y, z;
	};
	#endif
#endif

class Triangle : public PrimitiveBase
{
public:
	Triangle()
#ifdef USING_GL_COMMON
		: shaderID(0) {}
#elif defined(USING_D3D11)
	{}
#endif

#ifdef USING_D3D11
	struct CBuffer
	{
		CMatrix4D WVP;
		CMatrix4D World;
	};
#endif

	void Create();
	void Create(char *) {}
	void Transform(CMatrix4D * t);
	void Draw(CMatrix4D * t, CMatrix4D * vp);
	void Destroy();

#ifdef USING_GL_COMMON
	GLuint	shaderID;
	GLuint	vertexAttribLoc;
	GLuint	colorAttribLoc;

	GLuint  matUniformLoc;
#ifdef USE_VBO
	triVertex		vertices[4];
	unsigned short	indices[6];
	GLuint			VB;
	GLuint			IB;
#else
	#ifdef USE_ARRAY_OF_STRUCTS
		triVertex	vertices[6];
	#else
		triVertex	positions[6];
		triVertex	colors[6];
	#endif
#endif
#elif defined(USING_D3D11)
	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11VertexShader>  pVS;
	ComPtr<ID3D11PixelShader>   pFS;
	ComPtr<ID3DBlob>            VS_blob;
	ComPtr<ID3DBlob>            FS_blob;
	ComPtr<ID3D11InputLayout>   Layout;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;

	Triangle::CBuffer	CnstBuffer;
	triVertex		vertices[4];
	unsigned short	indices[6];
#endif

	CMatrix4D	transform;
};

#endif