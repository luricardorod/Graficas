#ifndef PATO_PRIMITIVEBASE_H
#define PATO_PRIMITIVEBASE_H

#include "../Config.h"

#include <scene/SceneProp.h>
#include <video/BaseDriver.h>

#include <vector>

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#endif

struct simplefloat16
{
	float v[16];
};

struct simplefloat4
{
	float v[4];
};

struct CVertex
{
	float x, y, z, w;		//0
	float nx, ny, nz, nw;	//16
	float bx, by, bz, bw;	//32
	float tx, ty, tz, tw;	//48
	float s, t;				//64
	float weight;			//72
};

class PrimitiveBase
{
public:
	PrimitiveBase() : pScProp(0) , gSig(0)
	{
		for (int i = 0; i < 8; i++)
			Textures[i] = 0;
	}
	virtual ~PrimitiveBase(){}
	virtual void Create() = 0;
	virtual void Create(char *) = 0;
	virtual void Transform(CMatrix4D * t) = 0;
	virtual void Draw(CMatrix4D * t, CMatrix4D * vp) = 0;
	virtual void Destroy() = 0;

	void SetGlobalSignature(unsigned int f){ gSig = f; }
	void SetTexture(Texture* tex,int index)
	{
		Textures[index] = tex;
	}

	void SetSceneProps(SceneProps *p) { pScProp = p; }
	SceneProps * pScProp;
	Texture * Textures[8];
	bool wireframeMode;
	unsigned int gSig;
};

#endif