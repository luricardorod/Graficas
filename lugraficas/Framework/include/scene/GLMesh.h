#ifndef PATO_MESH_GL_H
#define PATO_MESH_GL_H

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
#ifdef OS_WINDOWS
#include <GL/glew.h>
#elif defined(OS_LINUX)
#include <GL/gl.h>
#endif
#include <video/GLTexture.h>
#endif

#include <video/BaseDriver.h>
#include <utils/Utils.h>
#include <CMatrix4D.h>
#include <scene/PrimitiveBase.h>

#include <vector>

class GLMesh : public PrimitiveBase
{
public:
	GLMesh() {}
	/*
	struct SubSetInfo
	{
		unsigned int		Sig;

		unsigned long		VertexAttrib;
		unsigned int		Id;
		int		IdDiffuseTex;
		int		IdSpecularTex;
		int		IdGlossTex;
		int		IdNormalTex;
		int		IdReflectTex;
		int		IdTexUniformLoc;


		int					DiffuseId;
		int					SpecularId;
		int					GlossfId;
		int					NormalId;
		int					ReflectId;

		unsigned int		VertexStart;
		unsigned int		NumVertex;
		unsigned int		TriStart;
		unsigned int		NumTris;
		unsigned int		VertexSize;
		bool				bAlignedVertex;
	};

	struct MeshInfo
	{
		unsigned int VertexSize;
		unsigned int NumVertex;

		unsigned int Id;
		unsigned int IdIBO;

		std::vector<SubSetInfo>	SubSets;
	};
	*/

	void Create() {}
	void Create(char * filename);
	void Transform(CMatrix4D * t);
	void Draw(CMatrix4D * t, CMatrix4D * vp);
	void Destroy();

	void GatherInfo();
	/*
	int  LoadTex(std::string p, xF::xMaterial *mat);
	CMatrix4D	transform;
	XDataBase	xFile;
	std::vector<MeshInfo> Info;
	*/
};

#endif