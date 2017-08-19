#ifndef UAD_COBJECT3D_GL_H
#define UAD_COBJECT3D_GL_H

#include "Config.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <video\GLTexture.h>


#include "CMatrix4D.h"
#include "PrimitiveBase.h"
#include <utils\Utils.h>
#include <vector>


struct textureByMesh
{
	bool specular;
	bool gloss;
	bool normal;
	char* specularName;
	char* glossName;
	char* normalName;
	char *diffuseName;
	int  idSpecular;
	int  idNormal;
	int  idDiffuse;
	int	 idGloss;
};

struct infotex {
public:
	unsigned short numberOfTextures;
	std::vector<unsigned short> indicesTextures;
	std::vector<textureByMesh> textures;
};

class GLMesh : public PrimitiveBase {

public:
	//std::vector<Bones> bones;
	CMatrix4D	transform;

	void Create(char * path);
	void Transform(CMatrix4D *t);
	void Draw(CMatrix4D *t, CMatrix4D *vp);
	void Destroy();
	bool viewWareFrame = true;
	struct BonsInlfluenceForVertex
	{
		std::vector<int> bones;
		std::vector<float> influence;
	};
	struct mesh {
		GLuint			VB;
		GLuint			IBMesh;

		GLuint			IB[20];
		std::vector<CVertex> bufferVertex;
		std::vector<unsigned short> meshbufferIndex;
		std::vector<unsigned short> bufferIndex;
		infotex infoTexture;
		std::vector<std::vector<unsigned short>*> bufferIndexForTextures;
		std::vector<BonsInlfluenceForVertex> bonsInlfluenceForVertex;

	};

	GLMesh() : shaderID(0), shaderWireFrame(0) {}

	GLuint	shaderID;
	GLuint	shaderWireFrame;
	GLint	vertexAttribLocSimple;
	GLint   matWorldViewProjUniformLocSimple;

	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	binormalAttribLoc;
	GLint	tangenteAttribLoc;
	GLint	uvAttribLoc;
	GLint	normalLoc;
	GLint	diffuseLoc;
	GLint	specularLoc;
	GLint	glossLoc;

	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;


	GLint DirectionGlobalLight;
	GLint ColorGlobalLight;
	GLint PositionPointLight;
	GLint ColorPointLight;
	GLint PosCamera;

	int AddBone(char* archivo, int counter, int father);
	void AddChildsAndBrothers();
	std::vector<mesh> meshes;

};


#endif