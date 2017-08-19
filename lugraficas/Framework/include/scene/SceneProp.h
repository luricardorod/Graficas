#ifndef PATO_SCENEPROPS_H
#define PATO_SCENEPROPS_H

#include "../Config.h"

#include <CMatrix4D.h>
#include <utils/Camera.h>
#include <vector>

struct Light
{
	CVector4D Position;
	CVector4D Color;
	int		 Type;
	int		 Enabled;
};

struct SceneProps
{
	SceneProps() : ActiveCamera(0) , ActiveLights(1), ActiveLightCamera(0){}

	void	AddLight(CVector4D Pos, CVector4D Color,bool enabled);
	void	RemoveLight(unsigned int index);
	void	SetLightPos(unsigned int index, CVector4D);

	void	AddCamera(Camera*);
	void	RemoveCamera(unsigned int index);

	void	AddLightCamera(Camera*);
	void	RemoveLightCamera(unsigned int index);

	std::vector<Light>	   Lights;
	std::vector<Camera*> pCameras;

	std::vector<Camera*> pLightCameras;

	CVector4D			AmbientColor;

	int ActiveCamera;
	int	ActiveLights;
	int ActiveLightCamera;
};

#endif