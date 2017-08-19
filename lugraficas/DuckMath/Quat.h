#pragma once
#include <math.h>
#include <cstring>

class CQuaternion
{
public: //Public Methdos
	CQuaternion();
	~CQuaternion();

	CQuaternion(float fx, float fy, float fz, float fw);
	CQuaternion(float * v4);

	CQuaternion operator+(CQuaternion & Q);
	CQuaternion operator-(CQuaternion & Q);
	CQuaternion operator*(CQuaternion & Q);
	CQuaternion operator/(CQuaternion & Q);
	float Measure();
	CQuaternion Conjugate();
	CQuaternion operator*(float s);
	CQuaternion Normalize();
	CQuaternion Rotation(CQuaternion & A, float theta);
	float Dot(CQuaternion & A);
	CQuaternion Slerp(CQuaternion & B, float proportion);

public: //Public atributes
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float v[4];
	};
};