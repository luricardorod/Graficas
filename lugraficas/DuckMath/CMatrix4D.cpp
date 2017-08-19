#include "CMatrix4D.h"

#define ManoDer 1
#define ManoIzq 2

#define ManoAUsar ManoDer

CVector4D CVector4D::operator*(CMatrix4D & M)
{
	CVector4D R(0.0f, 0.0f, 0.0f, 1.0f);

	R.x += this->v[0] * M.m[0][0];
	R.x += this->v[1] * M.m[1][0];
	R.x += this->v[2] * M.m[2][0];
	R.x += this->v[3] * M.m[3][0];

	R.y += this->v[0] * M.m[0][1];
	R.y += this->v[1] * M.m[1][1];
	R.y += this->v[2] * M.m[2][1];
	R.y += this->v[3] * M.m[3][1];

	R.z += this->v[0] * M.m[0][2];
	R.z += this->v[1] * M.m[1][2];
	R.z += this->v[2] * M.m[2][2];
	R.z += this->v[3] * M.m[3][2];

	R.w += this->v[0] * M.m[0][3];
	R.w += this->v[1] * M.m[1][3];
	R.w += this->v[2] * M.m[2][3];
	R.w += this->v[3] * M.m[3][3];

	return R;
}

CVector4D & CVector4D::operator*=(CMatrix4D & M)
{
	return (*this)*M;
}

CMatrix4D::CMatrix4D()
{

}

CMatrix4D::CMatrix4D(float a00, float a01, float a02, float a03, float a10, float a11, float a12, float a13, float a20, float a21, float a22, float a23, float a30, float a31, float a32, float a33) :
	m00(a00), m01(a01), m02(a02), m03(a03),
	m10(a10), m11(a11), m12(a12), m13(a13),
	m20(a20), m21(a21), m22(a22), m23(a23),
	m30(a30), m31(a31), m32(a32), m33(a33)
{

}

CMatrix4D::CMatrix4D(CMatrix4D & M)
{
	memcpy(v, M.v, 64);
}

CMatrix4D::CMatrix4D(CVector4D & row0, CVector4D & row1, CVector4D & row2, CVector4D & row3)
{
	memcpy(m[0], row0.v, 16);
	memcpy(m[1], row1.v, 16);
	memcpy(m[2], row2.v, 16);
	memcpy(m[3], row3.v, 16);
}

CMatrix4D::~CMatrix4D()
{

}

CMatrix4D & CMatrix4D::operator=(const CMatrix4D & B)
{
	memcpy(v, B.v, 64);

	return *this;
}

CMatrix4D CMatrix4D::operator*(const CMatrix4D & B)
{
	CMatrix4D R;
	/*
	float
		a00 = m00, a01 = m01, a02 = m02, a03 = m03,
		a10 = m10, a11 = m11, a12 = m12, a13 = m13,
		a20 = m20, a21 = m21, a22 = m22, a23 = m23,
		a30 = m30, a31 = m31, a32 = m32, a33 = m33;

	float
		b00 = B.m00, b01 = B.m01, b02 = B.m02, b03 = B.m03,
		b10 = B.m10, b11 = B.m11, b12 = B.m12, b13 = B.m13,
		b20 = B.m20, b21 = B.m21, b22 = B.m22, b23 = B.m23,
		b30 = B.m30, b31 = B.m31, b32 = B.m32, b33 = B.m33;


	/////////////////////////////////
	R.m00 = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
	R.m01 = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
	R.m02 = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
	R.m03 = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;
	/////////////////////////////////
	R.m10 = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
	R.m11 = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
	R.m12 = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
	R.m13 = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;
	/////////////////////////////////
	R.m20 = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
	R.m21 = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
	R.m22 = a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32;
	R.m23 = a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33;
	/////////////////////////////////
	R.m30 = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;
	R.m31 = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;
	R.m32 = a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32;
	R.m33 = a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33;
	/////////////////////////////////
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	float
		b00 = B.m00, b01 = B.m01, b02 = B.m02, b03 = B.m03,
		b10 = B.m10, b11 = B.m11, b12 = B.m12, b13 = B.m13,
		b20 = B.m20, b21 = B.m21, b22 = B.m22, b23 = B.m23,
		b30 = B.m30, b31 = B.m31, b32 = B.m32, b33 = B.m33;


	/////////////////////////////////
	R.m00 = m00 * b00 + m01 * b10 + m02 * b20 + m03 * b30;
	R.m01 = m00 * b01 + m01 * b11 + m02 * b21 + m03 * b31;
	R.m02 = m00 * b02 + m01 * b12 + m02 * b22 + m03 * b32;
	R.m03 = m00 * b03 + m01 * b13 + m02 * b23 + m03 * b33;
	/////////////////////////////////
	R.m10 = m10 * b00 + m11 * b10 + m12 * b20 + m13 * b30;
	R.m11 = m10 * b01 + m11 * b11 + m12 * b21 + m13 * b31;
	R.m12 = m10 * b02 + m11 * b12 + m12 * b22 + m13 * b32;
	R.m13 = m10 * b03 + m11 * b13 + m12 * b23 + m13 * b33;
	/////////////////////////////////
	R.m20 = m20 * b00 + m21 * b10 + m22 * b20 + m23 * b30;
	R.m21 = m20 * b01 + m21 * b11 + m22 * b21 + m23 * b31;
	R.m22 = m20 * b02 + m21 * b12 + m22 * b22 + m23 * b32;
	R.m23 = m20 * b03 + m21 * b13 + m22 * b23 + m23 * b33;
	/////////////////////////////////
	R.m30 = m30 * b00 + m31 * b10 + m32 * b20 + m33 * b30;
	R.m31 = m30 * b01 + m31 * b11 + m32 * b21 + m33 * b31;
	R.m32 = m30 * b02 + m31 * b12 + m32 * b22 + m33 * b32;
	R.m33 = m30 * b03 + m31 * b13 + m32 * b23 + m33 * b33;
	/////////////////////////////////
	/*
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	float b[4][4];

	memcpy(b, B.m, 64);


	/////////////////////////////////
	R.m00 = m00 * b[0][0] + m01 * b[1][0] + m02 * b[2][0] + m03 * b[3][0];
	R.m01 = m00 * b[0][1] + m01 * b[1][1] + m02 * b[2][1] + m03 * b[3][1];
	R.m02 = m00 * b[0][2] + m01 * b[1][2] + m02 * b[2][2] + m03 * b[3][2];
	R.m03 = m00 * b[0][3] + m01 * b[1][3] + m02 * b[2][3] + m03 * b[3][3];
	/////////////////////////////////
	R.m10 = m10 * b[0][0] + m11 * b[1][0] + m12 * b[2][0] + m13 * b[3][0];
	R.m11 = m10 * b[0][1] + m11 * b[1][1] + m12 * b[2][1] + m13 * b[3][1];
	R.m12 = m10 * b[0][2] + m11 * b[1][2] + m12 * b[2][2] + m13 * b[3][2];
	R.m13 = m10 * b[0][3] + m11 * b[1][3] + m12 * b[2][3] + m13 * b[3][3];
	/////////////////////////////////
	R.m20 = m20 * b[0][0] + m21 * b[1][0] + m22 * b[2][0] + m23 * b[3][0];
	R.m21 = m20 * b[0][1] + m21 * b[1][1] + m22 * b[2][1] + m23 * b[3][1];
	R.m22 = m20 * b[0][2] + m21 * b[1][2] + m22 * b[2][2] + m23 * b[3][2];
	R.m23 = m20 * b[0][3] + m21 * b[1][3] + m22 * b[2][3] + m23 * b[3][3];
	/////////////////////////////////
	R.m30 = m30 * b[0][0] + m31 * b[1][0] + m32 * b[2][0] + m33 * b[3][0];
	R.m31 = m30 * b[0][1] + m31 * b[1][1] + m32 * b[2][1] + m33 * b[3][1];
	R.m32 = m30 * b[0][2] + m31 * b[1][2] + m32 * b[2][2] + m33 * b[3][2];
	R.m33 = m30 * b[0][3] + m31 * b[1][3] + m32 * b[2][3] + m33 * b[3][3];
	/////////////////////////////////
	*/

	return R;
}

CMatrix4D & CMatrix4D::operator*=(const CMatrix4D & B)
{
	CMatrix4D Result = (*this)*B;
	return Result;
}

CVector4D CMatrix4D::operator*(const CVector4D & V)
{
	
	return CVector4D(
		CVector4D(m00, m01, m02, m03).Dot(V),
		CVector4D(m10, m11, m12, m13).Dot(V),
		CVector4D(m20, m21, m22, m23).Dot(V),
		CVector4D(m30, m31, m32, m33).Dot(V)
	);
}

CVector4D & CMatrix4D::operator*=(const CVector4D & V)
{
	return (*this)*V;
}

CMatrix4D CMatrix4D::Zero()
{
	CMatrix4D ZeroMatrix;
	memset(ZeroMatrix.m, 0, 64);
	return ZeroMatrix;
}

CMatrix4D CMatrix4D::Identity()
{
	CMatrix4D IdentityMatrix;
	memset(IdentityMatrix.m, 0, 64);

	IdentityMatrix.m00 = 1.0f;
	IdentityMatrix.m11 = 1.0f;
	IdentityMatrix.m22 = 1.0f;
	IdentityMatrix.m33 = 1.0f;

	return IdentityMatrix;
}

CMatrix4D CMatrix4D::Translation(float dx, float dy, float dz)
{
	CMatrix4D Result;

	memset(Result.m, 0, 64);

	Result.m00 = 1.0f;
	Result.m11 = 1.0f;
	Result.m22 = 1.0f;
	Result.m33 = 1.0f;

	Result.m30 = dx;
	Result.m31 = dy;
	Result.m32 = dz;

	return Result;
}

CMatrix4D CMatrix4D::RotationX(float theta)
{
	CMatrix4D R;

	memset(R.m, 0, 64);

	R.m00 = 1.0f;
	R.m33 = 1.0f;

	R.m11 = cosf(theta);
	R.m22 = R.m11;
	R.m21 = sinf(theta);
	R.m12 = -R.m21;

	return R;
}

CMatrix4D CMatrix4D::RotationY(float theta)
{
	CMatrix4D R;

	memset(R.m, 0, 64);

	R.m11 = 1.0f;
	R.m33 = 1.0f;

	R.m00 = cosf(theta);
	R.m22 = R.m00;
	R.m02 = sinf(theta);
	R.m20 = -R.m02;

	return R;
}

CMatrix4D CMatrix4D::RotationZ(float theta)
{
	CMatrix4D R;

	memset(R.m, 0, 64);

	R.m22 = 1.0f;
	R.m33 = 1.0f;

	R.m00 = cosf(theta);
	R.m11 = R.m00;
	R.m10 = sinf(theta);
	R.m01 = -R.m10;
	return R;
}

CMatrix4D CMatrix4D::RotationOverAxis(CVector4D & Axis, float Angle)
{
	float c = cos(Angle);
	float s = sin(Angle);
	float t = 1.0f - c;

	CVector4D NormalizedAxis = Axis.Normalize();

	float x = NormalizedAxis.x;
	float y = NormalizedAxis.y;
	float z = NormalizedAxis.z;

	CMatrix4D Result;

	Result.m00 = 1.0f + t*(x*x - 1.0f);
	Result.m01 = z*s + t*x*y;
	Result.m02 = t*x*z - y*s;
	Result.m03 = 0.0f;

	Result.m10 = t*x*y - z*s;
	Result.m11 = 1.0f + t*(y*y - 1.0f);
	Result.m12 = x*s + t*y*z;
	Result.m13 = 0.0f;

	Result.m20 = y*s + t*x*z;
	Result.m21 = -x*s + t*y*z;
	Result.m22 = 1.0f + t*(z*z - 1.0f);
	Result.m23 = 0.0f;

	Result.m30 = 0.0f;
	Result.m31 = 0.0f;
	Result.m32 = 0.0f;
	Result.m33 = 1.0f;

	return Result;
}

CMatrix4D CMatrix4D::Scaling(float sx, float sy, float sz)
{
	CMatrix4D Result;

	memset(Result.m, 0, 64);

	Result.m00 = sx;
	Result.m11 = sy;
	Result.m22 = sz;
	Result.m33 = 1.0f;

	return Result;
}

float CMatrix4D::Det89(CMatrix4D & M)
{
	return 0.0f;
}

CMatrix4D CMatrix4D::Transpose(CMatrix4D &M)
{
	return CMatrix4D();
}

CMatrix4D CMatrix4D::Cofactors(CMatrix4D &M)
{
	return CMatrix4D();
}

CMatrix4D CMatrix4D::Inverse()
{
	/*
	CMatrix4D tmp64 = *this;
	float det =
		tmp64.m00*tmp64.m11*tmp64.m22*tmp64.m33 + tmp64.m00*tmp64.m12*tmp64.m23*tmp64.m31 + tmp64.m00*tmp64.m13*tmp64.m21*tmp64.m32
		+ tmp64.m01*tmp64.m10*tmp64.m23*tmp64.m32 + tmp64.m01*tmp64.m12*tmp64.m20*tmp64.m33 + tmp64.m01*tmp64.m13*tmp64.m22*tmp64.m30
		+ tmp64.m02*tmp64.m10*tmp64.m21*tmp64.m33 + tmp64.m02*tmp64.m11*tmp64.m23*tmp64.m30 + tmp64.m02*tmp64.m13*tmp64.m20*tmp64.m31
		+ tmp64.m03*tmp64.m10*tmp64.m22*tmp64.m31 + tmp64.m03*tmp64.m11*tmp64.m20*tmp64.m32 + tmp64.m03*tmp64.m12*tmp64.m21*tmp64.m30
		- tmp64.m00*tmp64.m11*tmp64.m23*tmp64.m32 - tmp64.m00*tmp64.m12*tmp64.m21*tmp64.m33 - tmp64.m00*tmp64.m13*tmp64.m22*tmp64.m31
		- tmp64.m01*tmp64.m10*tmp64.m22*tmp64.m33 - tmp64.m01*tmp64.m12*tmp64.m23*tmp64.m30 - tmp64.m01*tmp64.m13*tmp64.m20*tmp64.m32
		- tmp64.m02*tmp64.m10*tmp64.m23*tmp64.m31 - tmp64.m02*tmp64.m11*tmp64.m20*tmp64.m33 - tmp64.m02*tmp64.m13*tmp64.m21*tmp64.m30
		- tmp64.m03*tmp64.m10*tmp64.m21*tmp64.m32 - tmp64.m03*tmp64.m11*tmp64.m22*tmp64.m30 - tmp64.m03*tmp64.m12*tmp64.m20*tmp64.m31;

	if (det == 0.0f)
		exit(666);

	det = 1.0f / det;
	CMatrix4D out;

	out.m00 = tmp64.m11*tmp64.m22*tmp64.m33 + tmp64.m12*tmp64.m23*tmp64.m31 + tmp64.m13*tmp64.m21*tmp64.m32 - tmp64.m11*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m21*tmp64.m33 - tmp64.m13*tmp64.m22*tmp64.m31;
	out.m01 = tmp64.m01*tmp64.m23*tmp64.m32 + tmp64.m02*tmp64.m21*tmp64.m33 + tmp64.m03*tmp64.m22*tmp64.m31 - tmp64.m01*tmp64.m22*tmp64.m33 - tmp64.m02*tmp64.m23*tmp64.m31 - tmp64.m03*tmp64.m21*tmp64.m32;
	out.m02 = tmp64.m01*tmp64.m12*tmp64.m33 + tmp64.m02*tmp64.m13*tmp64.m31 + tmp64.m03*tmp64.m11*tmp64.m32 - tmp64.m01*tmp64.m13*tmp64.m32 - tmp64.m02*tmp64.m11*tmp64.m33 - tmp64.m03*tmp64.m12*tmp64.m31;
	out.m03 = tmp64.m01*tmp64.m13*tmp64.m22 + tmp64.m02*tmp64.m11*tmp64.m23 + tmp64.m03*tmp64.m12*tmp64.m21 - tmp64.m01*tmp64.m12*tmp64.m23 - tmp64.m02*tmp64.m13*tmp64.m21 - tmp64.m03*tmp64.m11*tmp64.m22;
	out.m10 = tmp64.m10*tmp64.m23*tmp64.m32 + tmp64.m12*tmp64.m20*tmp64.m33 + tmp64.m13*tmp64.m22*tmp64.m30 - tmp64.m10*tmp64.m22*tmp64.m33 - tmp64.m12*tmp64.m23*tmp64.m30 - tmp64.m13*tmp64.m20*tmp64.m32;
	out.m11 = tmp64.m00*tmp64.m22*tmp64.m33 + tmp64.m02*tmp64.m23*tmp64.m30 + tmp64.m03*tmp64.m20*tmp64.m32 - tmp64.m00*tmp64.m23*tmp64.m32 - tmp64.m02*tmp64.m20*tmp64.m33 - tmp64.m03*tmp64.m22*tmp64.m30;
	out.m12 = tmp64.m00*tmp64.m13*tmp64.m32 + tmp64.m02*tmp64.m10*tmp64.m33 + tmp64.m03*tmp64.m12*tmp64.m30 - tmp64.m00*tmp64.m12*tmp64.m33 - tmp64.m02*tmp64.m13*tmp64.m30 - tmp64.m03*tmp64.m10*tmp64.m32;
	out.m13 = tmp64.m00*tmp64.m12*tmp64.m23 + tmp64.m02*tmp64.m13*tmp64.m20 + tmp64.m03*tmp64.m10*tmp64.m22 - tmp64.m00*tmp64.m13*tmp64.m22 - tmp64.m02*tmp64.m10*tmp64.m23 - tmp64.m03*tmp64.m12*tmp64.m20;
	out.m20 = tmp64.m10*tmp64.m21*tmp64.m33 + tmp64.m11*tmp64.m23*tmp64.m30 + tmp64.m13*tmp64.m20*tmp64.m31 - tmp64.m10*tmp64.m23*tmp64.m31 - tmp64.m11*tmp64.m20*tmp64.m33 - tmp64.m13*tmp64.m21*tmp64.m30;
	out.m21 = tmp64.m00*tmp64.m23*tmp64.m31 + tmp64.m01*tmp64.m20*tmp64.m33 + tmp64.m03*tmp64.m21*tmp64.m30 - tmp64.m00*tmp64.m21*tmp64.m33 - tmp64.m01*tmp64.m23*tmp64.m30 - tmp64.m03*tmp64.m20*tmp64.m31;
	out.m22 = tmp64.m00*tmp64.m11*tmp64.m33 + tmp64.m01*tmp64.m13*tmp64.m30 + tmp64.m03*tmp64.m10*tmp64.m31 - tmp64.m00*tmp64.m13*tmp64.m31 - tmp64.m01*tmp64.m10*tmp64.m33 - tmp64.m03*tmp64.m11*tmp64.m30;
	out.m23 = tmp64.m00*tmp64.m13*tmp64.m21 + tmp64.m01*tmp64.m10*tmp64.m23 + tmp64.m03*tmp64.m11*tmp64.m20 - tmp64.m00*tmp64.m11*tmp64.m23 - tmp64.m01*tmp64.m13*tmp64.m20 - tmp64.m03*tmp64.m10*tmp64.m21;
	out.m30 = tmp64.m10*tmp64.m22*tmp64.m31 + tmp64.m11*tmp64.m20*tmp64.m32 + tmp64.m12*tmp64.m21*tmp64.m30 - tmp64.m10*tmp64.m21*tmp64.m32 - tmp64.m11*tmp64.m22*tmp64.m30 - tmp64.m12*tmp64.m20*tmp64.m31;
	out.m31 = tmp64.m00*tmp64.m21*tmp64.m32 + tmp64.m01*tmp64.m22*tmp64.m30 + tmp64.m02*tmp64.m20*tmp64.m31 - tmp64.m00*tmp64.m22*tmp64.m31 - tmp64.m01*tmp64.m20*tmp64.m32 - tmp64.m02*tmp64.m21*tmp64.m30;
	out.m32 = tmp64.m00*tmp64.m12*tmp64.m31 + tmp64.m01*tmp64.m10*tmp64.m32 + tmp64.m02*tmp64.m11*tmp64.m30 - tmp64.m00*tmp64.m11*tmp64.m32 - tmp64.m01*tmp64.m12*tmp64.m30 - tmp64.m02*tmp64.m10*tmp64.m31;
	out.m33 = tmp64.m00*tmp64.m11*tmp64.m22 + tmp64.m01*tmp64.m12*tmp64.m20 + tmp64.m02*tmp64.m10*tmp64.m21 - tmp64.m00*tmp64.m12*tmp64.m21 - tmp64.m01*tmp64.m10*tmp64.m22 - tmp64.m02*tmp64.m11*tmp64.m20;

	CMatrix4D tmpO;

	for (int i = 0; i < 16; i++)
		tmpO.v[i] = det*out.v[i];

	return tmpO;
	*/

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	//
	// Inversion by Cramer's rule.  Code taken from an Intel publication
	//
	double Result[4][4];
	double tmp[12]; /* temp array for pairs */
	double src[16]; /* array of transpose source matrix */
	double det; /* determinant */
				/* transpose matrix */
	for (unsigned int i = 0; i < 4; i++)
	{
		src[i + 0] = (*this).m[i][0];
		src[i + 4] = (*this).m[i][1];
		src[i + 8] = (*this).m[i][2];
		src[i + 12] = (*this).m[i][3];
	}
	/* calculate pairs for first 8 elements (cofactors) */
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];
	/* calculate first 8 elements (cofactors) */
	Result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	Result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	Result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	Result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	Result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	Result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	Result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	Result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	Result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	Result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	Result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	Result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	Result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	Result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	Result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	Result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
	/* calculate pairs for second 8 elements (cofactors) */
	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];

	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];
	/* calculate second 8 elements (cofactors) */
	Result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	Result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	Result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	Result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	Result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	Result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	Result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	Result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	Result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	Result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	Result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	Result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	Result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	Result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	Result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	Result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
	/* calculate determinant */
	det = src[0] * Result[0][0] + src[1] * Result[0][1] + src[2] * Result[0][2] + src[3] * Result[0][3];
	/* calculate matrix inverse */
	det = 1.0f / det;

	CMatrix4D FloatResult;
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
			FloatResult.m[i][j] = float(Result[i][j] * det);
	}
	return FloatResult;

	//
	// Inversion by LU decomposition, alternate implementation
	//
	/*int i, j, k;

	for (i = 1; i < 4; i++)
	{
	_Entries[0][i] /= _Entries[0][0];
	}

	for (i = 1; i < 4; i++)
	{
	for (j = i; j < 4; j++)
	{
	float sum = 0.0;
	for (k = 0; k < i; k++)
	{
	sum += _Entries[j][k] * _Entries[k][i];
	}
	_Entries[j][i] -= sum;
	}
	if (i == 4-1) continue;
	for (j=i+1; j < 4; j++)
	{
	float sum = 0.0;
	for (int k = 0; k < i; k++)
	sum += _Entries[i][k]*_Entries[k][j];
	_Entries[i][j] =
	(_Entries[i][j]-sum) / _Entries[i][i];
	}
	}

	//
	// Invert L
	//
	for ( i = 0; i < 4; i++ )
	{
	for ( int j = i; j < 4; j++ )
	{
	float x = 1.0;
	if ( i != j )
	{
	x = 0.0;
	for ( int k = i; k < j; k++ )
	x -= _Entries[j][k]*_Entries[k][i];
	}
	_Entries[j][i] = x / _Entries[j][j];
	}
	}

	//
	// Invert U
	//
	for ( i = 0; i < 4; i++ )
	{
	for ( j = i; j < 4; j++ )
	{
	if ( i == j ) continue;
	float sum = 0.0;
	for ( int k = i; k < j; k++ )
	sum += _Entries[k][j]*( (i==k) ? 1.0f : _Entries[i][k] );
	_Entries[i][j] = -sum;
	}
	}

	//
	// Final Inversion
	//
	for ( i = 0; i < 4; i++ )
	{
	for ( int j = 0; j < 4; j++ )
	{
	float sum = 0.0;
	for ( int k = ((i>j)?i:j); k < 4; k++ )
	sum += ((j==k)?1.0f:_Entries[j][k])*_Entries[k][i];
	_Entries[j][i] = sum;
	}
	}*/
}

CMatrix4D CMatrix4D::LookAtLH(CVector4D &EyePos, CVector4D &Target, CVector4D &Up)
{
	CVector4D zaxis = (Target - EyePos).Normalize();
	CVector4D xaxis = (Up.Cross3(zaxis)).Normalize();
	CVector4D yaxis = zaxis.Cross3(xaxis);

	CMatrix4D View(
		xaxis.x, yaxis.x, zaxis.x, 0.0f,
		xaxis.y, yaxis.y, zaxis.y, 0.0f,
		xaxis.z, yaxis.z, zaxis.z, 0.0f,
		-xaxis.Dot(EyePos), -yaxis.Dot(EyePos), -zaxis.Dot(EyePos), 1.0f
	);
	return View;
}

CMatrix4D CMatrix4D::LookAtRH(CVector4D &EyePos, CVector4D &Target, CVector4D &Up)
{
	CVector4D zaxis = (EyePos - Target).Normalize();
	CVector4D xaxis = (Up.Cross3(zaxis)).Normalize();
	CVector4D yaxis = zaxis.Cross3(xaxis);
	CMatrix4D View(
		xaxis.x, yaxis.x, zaxis.x, 0.0f,
		xaxis.y, yaxis.y, zaxis.y, 0.0f,
		xaxis.z, yaxis.z, zaxis.z, 0.0f,
		-xaxis.Dot(EyePos), -yaxis.Dot(EyePos), -zaxis.Dot(EyePos), 1.0f
	);
	return View;
}

CMatrix4D CMatrix4D::Orthogonal(float Width, float Height, float ZNear, float ZFar)
{
	CMatrix4D Result;

	memset(Result.m, 0, 64);

	/*
	Result.m00 = 2.0f / Width;
	Result.m11 = 2.0f / Height;
	Result.m22 = 1.0f / (ZFar - ZNear);
	Result.m32 = ZNear / (ZNear - ZFar);
	Result.m33 = 1.0f;
	*/

	Result.m00 = -2.0f / Width;
	Result.m11 = 2.0f / Height;
	Result.m22 = 1.0f / (ZFar - ZNear);
	//Result.m23 = -1.0f;
	//Result.m32 = ZNear / (ZNear - ZFar);
	Result.m32 = 0.5f;
	Result.m33 = 1.0f;

	return Result;
}

CMatrix4D CMatrix4D::Perspective(float Width, float Height, float ZNear, float ZFar)
{
	CMatrix4D Result;

	memset(Result.m, 0, 64);

	Result.m00 = -2.0f * ZNear / Width;
	Result.m11 = 2.0f * ZNear / Height;
	Result.m22 = ZFar / (ZNear - ZFar);
	Result.m23 = -1.0f;
	Result.m32 = (ZFar * ZNear) / (ZNear - ZFar);

	return Result;
}

CMatrix4D CMatrix4D::PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar)
{
	float Width = 1.0f / tanf(FOV / 2.0f);
	float Height = Aspect / tanf(FOV / 2.0f);

	CMatrix4D Result;

	memset(Result.m, 0, 64);

	Result.m00 = -Width;
	Result.m11 = Height;
	Result.m22 = ZFar / (ZNear - ZFar);
	Result.m23 = -1.0f;
	Result.m32 = ZFar * ZNear / (ZNear - ZFar);

	return Result;
}

CMatrix4D CMatrix4D::MatrixFromQuaternion(CQuaternion & Q)
{
	CMatrix4D pMatrix;

	pMatrix.v[0] = 1.0f - 2.0f * Q.y*Q.y - 2.0f * Q.z*Q.z;
	pMatrix.v[1] = 2.0f*Q.x*Q.y - 2.0f*Q.z*Q.w;
	pMatrix.v[2] = 2.0f*Q.x*Q.z + 2.0f*Q.w*Q.y;
	pMatrix.v[3] = 0.0f;

	pMatrix.v[4] = 2.0f*Q.x*Q.y + 2.0f *Q.z*Q.w;
	pMatrix.v[5] = 1.0f - 2.0f*Q.x*Q.x - 2.0f *Q.z*Q.z;
	pMatrix.v[6] = 2.0f*Q.y*Q.z - 2.0f*Q.x*Q.w;
	pMatrix.v[7] = 0.0f;

	pMatrix.v[8] = 2.0f*Q.x*Q.z - 2.0f*Q.y*Q.w;
	pMatrix.v[9] = 2.0f*Q.y*Q.z + 2.0f*Q.x*Q.w;
	pMatrix.v[10] = 1.0f - 2.0f*Q.x*Q.x - 2.0f*Q.y*Q.y;
	pMatrix.v[11] = 0.0f;

	pMatrix.v[12] = 0.0f;
	pMatrix.v[13] = 0.0f;
	pMatrix.v[14] = 0.0f;
	pMatrix.v[15] = 1.0f;

	return pMatrix;
}