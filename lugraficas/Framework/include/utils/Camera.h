#ifndef PATO_CAMERA_H
#define PATO_CAMERA_H

#include "../Config.h"

#include <CMatrix4D.h>


class Camera
{
public:
	Camera();

	void	Init(CVector4D position,float fov,float ratio,float np,float fp,bool lf=true);
	void	CreatePojection();

	void	Move(float locForward, float locUp, float locRight);

	void	Update();
	void	Reset();

	void	SetFov(float f);
	void	SetRotation(float rotateX, float rotateY, float rotateZ);
	void	SetRatio(float r);
	void	SetPlanes(float n, float f);

	float	Fov;
	float	AspectRatio;
	float	NPlane;
	float	FPlane;

	CVector4D	Eye;

	CMatrix4D	View;
	CMatrix4D	Projection;
	CMatrix4D	VP;

	CVector4D LocalForward;
	CVector4D LocalUp;
	CVector4D LocalRight;

	float m_fYaw, m_fPitch, m_fRoll;
	
	CMatrix4D Rotater;
};

#endif