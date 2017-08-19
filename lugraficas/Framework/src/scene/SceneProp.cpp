#include <scene/SceneProp.h>

void SceneProps::AddLight(CVector4D Pos, CVector4D Color, bool enabled)
{
	Light l;
	l.Position=Pos;
	l.Color=Color;
	l.Enabled=(int)enabled;
	Lights.push_back(l);
}

void SceneProps::RemoveLight(unsigned int index)
{
	if(index < 0 || index >= Lights.size())
		return;

	Lights.erase(Lights.begin() + index);
}

void SceneProps::SetLightPos(unsigned int index, CVector4D pos)
{
	if (index < 0 || index >= Lights.size())
		return;

	Lights[index].Position = pos;
}

void SceneProps::AddCamera(Camera* cam)
{
	pCameras.push_back(cam);
}

void SceneProps::RemoveCamera(unsigned int index)
{
	if (index < 0 || index >= pCameras.size())
		return;

	pCameras.erase(pCameras.begin() + index);
}

void SceneProps::AddLightCamera(Camera* cam)
{
	pLightCameras.push_back(cam);
}

void SceneProps::RemoveLightCamera(unsigned int index)
{
	if (index < 0 || index >= pLightCameras.size())
		return;

	pLightCameras.erase(pLightCameras.begin() + index);
}