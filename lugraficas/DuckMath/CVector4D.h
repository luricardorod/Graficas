#pragma once
#include <cstring>
#include <cmath>

#define Deg2Rad 0.01745329251f
#define Rad2Deg 57.2957795131f
#define PI 3.14159265359f

class CMatrix4D;

class CVector4D
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		float v[4];
	};

	CVector4D();
	CVector4D(const CVector4D & V);
	CVector4D(float fx, float fy, float fz, float fw);
	virtual ~CVector4D();

	CVector4D operator* (CVector4D & A);
	CVector4D & operator*= (CVector4D & A);
	CVector4D operator* (float S);
	CVector4D & operator*= (float S);
	CVector4D operator/ (float S);
	CVector4D & operator/= (float S);
	CVector4D operator+ (CVector4D & A);
	CVector4D & operator+= (CVector4D & A);
	CVector4D operator- (CVector4D & A);
	CVector4D & operator-= (CVector4D & A);

	CVector4D operator* (CMatrix4D & M);
	CVector4D & operator*= (CMatrix4D & M);

	CVector4D Cross3(CVector4D & A);
	float Dot(const CVector4D & A);
	float Magnitude();
	CVector4D Normalize();

	CVector4D Lerp(CVector4D & OtherValue, float proportion);
};