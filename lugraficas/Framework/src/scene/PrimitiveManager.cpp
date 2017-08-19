#include <scene/PrimitiveManager.h>
#include <scene/Triangle.h>
#include <scene/Cube.h>
#include <scene/GLMesh.h>
#include <scene/GLQuad.h>

#ifdef USING_D3D11
#include <scene/D3DXMesh.h>
#include <scene/D3DXQuad.h>
#endif

PrimitiveBase * PrimitiveManager::GetPrimitive(unsigned int index)
{
	if (index >= primitives.size())
		return 0;

	return primitives[index];
}

int PrimitiveManager::CreateTriangle()
{
	PrimitiveBase *primitive = new Triangle();
	primitive->Create();
	primitives.push_back(primitive);
	return (int)(primitives.size()-1);
}

int PrimitiveManager::CreateCube()
{
	PrimitiveBase *primitive = new Cube();
	primitive->Create();
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}

int PrimitiveManager::CreateMesh(char *fname)
{
#if defined(USING_GL_COMMON)
	PrimitiveBase *primitive = new GLMesh();
#elif defined(USING_D3D11)
	PrimitiveBase *primitive = new D3DXMesh();
#endif
	primitive->Create(fname);
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}

int PrimitiveManager::CreateQuad()
{
#if defined(USING_GL_COMMON)
	PrimitiveBase *primitive = new GLQuad();
#elif defined(USING_D3D11)
	PrimitiveBase *primitive = new D3DXQuad();
#endif
	primitive->Create();
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}

void PrimitiveManager::SetSceneProps(SceneProps * p)
{
	for (unsigned int i = 0; i < primitives.size(); i++)
		primitives[i]->SetSceneProps(p);
}

void PrimitiveManager::DrawPrimitives()
{
	for (unsigned int i = 0; i < primitives.size(); i++)
		primitives[i]->Draw(0, pVP);
}

void PrimitiveManager::DestroyPrimitives()
{
	for (unsigned int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->Destroy();
		delete primitives[i];
	}
	primitives.clear();
}