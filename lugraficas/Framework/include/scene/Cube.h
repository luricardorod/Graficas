#ifndef PATO_CUBE_GL_H
#define PATO_CUBE_GL_H

#include "../Config.h"

#include <utils/Utils.h>

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
#include <scene/PrimitiveBase.h>

class Cube : public PrimitiveBase
{
public:
	Cube()
#ifdef USING_GL_COMMON
	: shaderID(0)
#endif
	 {}

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
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;
	GLint	diffuseLoc;


	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;

	GLuint			VB;
	GLuint			IB;
#elif defined(USING_D3D11)
	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11VertexShader>  pVS;
	ComPtr<ID3D11PixelShader>   pFS;
	ComPtr<ID3DBlob>            VS_blob;
	ComPtr<ID3DBlob>            FS_blob;
	ComPtr<ID3D11InputLayout>   Layout;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;

	Cube::CBuffer	CnstBuffer;
#endif

	int		TexId;
	CVertex			vertices[24];
	unsigned short	indices[36];
	CMatrix4D	transform;
	Texture		*tex;
};

#endif