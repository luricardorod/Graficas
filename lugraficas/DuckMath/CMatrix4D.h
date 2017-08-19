#pragma once
#include "CVector4D.h"
#include "Quat.h"
#include "ExtraFunctions.h"

class CMatrix4D
{
public:
	union
	{
		struct
		{
			float
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33;
		};
		float m[4][4];
		float v[16];
	};
	CMatrix4D();
	CMatrix4D(float a00, float a01, float a02, float a03, float a10, float a11, float a12, float a13, float a20, float a21, float a22, float a23, float a30, float a31, float a32, float a33);
	CMatrix4D(CMatrix4D & M);
	CMatrix4D(CVector4D & row0, CVector4D & row1, CVector4D & row2, CVector4D & row3);
	~CMatrix4D();

	CMatrix4D & operator=(const CMatrix4D & B);
	CMatrix4D operator*(const CMatrix4D & B);
	CMatrix4D & operator*=(const CMatrix4D & B);
	CVector4D operator*(const CVector4D & V);
	CVector4D & operator*=(const CVector4D & V);

	CMatrix4D Zero();
	CMatrix4D Identity();
	CMatrix4D Translation(float dx, float dy, float dz);
	CMatrix4D RotationX(float theta);
	CMatrix4D RotationY(float theta);
	CMatrix4D RotationZ(float theta);
	CMatrix4D RotationOverAxis(CVector4D & Axis, float Angle);
	CMatrix4D Scaling(float sx, float sy, float sz);

	float Det89(CMatrix4D & M);
	CMatrix4D Transpose(CMatrix4D & M);
	CMatrix4D Cofactors(CMatrix4D & M);
	CMatrix4D Inverse();
	CMatrix4D LookAtLH(CVector4D & EyePos, CVector4D & Target, CVector4D & Up);
	CMatrix4D LookAtRH(CVector4D & EyePos, CVector4D & Target, CVector4D & Up);
	//CMatrix4D Orthographic
	CMatrix4D Orthogonal(float Width, float Height, float ZNear, float ZFar);
	CMatrix4D Perspective(float Width, float Height, float ZNear, float ZFar);
	CMatrix4D PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar);

	CMatrix4D MatrixFromQuaternion(CQuaternion & Q);
};