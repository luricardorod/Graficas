#include "CVector4D.h"

CVector4D::CVector4D()
{

}

CVector4D::CVector4D(const CVector4D & V)
{
	memcpy(v, V.v, 16);
}

CVector4D::CVector4D(float fx, float fy, float fz, float fw) : x(fx), y(fy), z(fz), w(fw)
{

}

CVector4D::~CVector4D()
{

}


CVector4D CVector4D::operator*(CVector4D & A)
{
	return CVector4D(x * A.x, y * A.y, z * A.z, w * A.w);
}

CVector4D & CVector4D::operator*=(CVector4D & A)
{
	return (*this)*A;
}

CVector4D CVector4D::operator*(float S)
{
	return CVector4D(x * S, y* S, z * S, w * S);
}

CVector4D & CVector4D::operator*=(float S)
{
	return (*this)*S;
}

CVector4D CVector4D::operator/(float S)
{
	if (S == 0)
		return CVector4D(0, 0, 0, 0);
	return (*this)*(1 / S);
}

CVector4D & CVector4D::operator/=(float S)
{
	return (*this) / S;
}

CVector4D CVector4D::operator+(CVector4D & A)
{
	return CVector4D(x + A.x, y + A.y, z + A.z, w + A.w);
}

CVector4D & CVector4D::operator+=(CVector4D & A)
{
	return (*this) + A;
}

CVector4D CVector4D::operator-(CVector4D & A)
{
	return CVector4D(x - A.x, y - A.y, z - A.z, w - A.w);
}

CVector4D & CVector4D::operator-=(CVector4D & A)
{
	return (*this) - A;
}


CVector4D CVector4D::Cross3(CVector4D & A)
{
	return CVector4D(
		y*A.z - z*A.y,
		z*A.x - x*A.z,
		x*A.y - y*A.x,
		0.0f
	);
}

float CVector4D::Dot(const CVector4D & A)
{
	return x * A.x + y * A.y + z * A.z + w * A.w;
}

float CVector4D::Magnitude()
{
	return sqrt(Dot(*this));
}

CVector4D CVector4D::Normalize()
{
	float myMagnitude = Magnitude();
	if (myMagnitude == 0)
		return CVector4D(0, 0, 0, 0);
	return (*this) / myMagnitude;
}

CVector4D CVector4D::Lerp(CVector4D & OtherValue, float proportion)
{
	return (*this + (OtherValue - *this)*proportion);
}