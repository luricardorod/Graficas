#ifndef PATO_PRIMITIVEMANAGER_H
#define PATO_PRIMITIVEMANAGER_H

#include "../Config.h"

#include <vector>
#include <CMatrix4D.h>
#include <scene/PrimitiveBase.h>
#include <scene/SceneProp.h>

class PrimitiveManager
{
public:
	void SetVP(CMatrix4D *vp)
	{
		pVP = vp;
	}
	int  CreateTriangle();
	int	 CreateCube();
	int	 CreateMesh(char *fname);
	int  CreateQuad();

	void SetSceneProps(SceneProps *p);

	void DrawPrimitives();
	void DestroyPrimitives();
	PrimitiveBase*	GetPrimitive(unsigned int);

	std::vector<PrimitiveBase*> primitives;

	CMatrix4D *pVP;
};

#endif