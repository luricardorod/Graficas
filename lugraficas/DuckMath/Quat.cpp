#include "Quat.h"

CQuaternion::CQuaternion()
{

}

CQuaternion::~CQuaternion()
{

}

CQuaternion::CQuaternion(float fx, float fy, float fz, float fw) : x(fx), y(fy), z(fz), w(fw)
{

}

CQuaternion::CQuaternion(float * v4)
{
	memcpy(v, v4, 16);
}

CQuaternion CQuaternion::operator+(CQuaternion & Q)
{
	return CQuaternion(x + Q.x, y + Q.y, z + Q.z, w + Q.w);
}

CQuaternion CQuaternion::operator-(CQuaternion & Q)
{
	return CQuaternion(x - Q.x, y - Q.y, z - Q.z, w - Q.w);
}

CQuaternion CQuaternion::operator*(CQuaternion & Q)
{
	return
		CQuaternion(
		(w * Q.x) + (y * Q.z) - (z * Q.y) + (x * Q.w),
		(w * Q.y) + (z * Q.x) - (x * Q.z) + (y * Q.w),
		(w * Q.z) + (x * Q.y) - (y * Q.x) + (z * Q.w),
		(w * Q.w) - (x * Q.x) - (y * Q.y) - (z * Q.z)
		);
}

CQuaternion CQuaternion::operator/(CQuaternion & Q)
{
	float invdiv = 1.0f / ( (Q.x + Q.x) + (Q.y + Q.y) + (Q.z + Q.z) + (Q.w + Q.w) );
	CQuaternion R = Q.Conjugate();
	R.x *= invdiv;
	R.y *= invdiv;
	R.z *= invdiv;
	R.w *= invdiv;
	return *this * R;
}

float CQuaternion::Measure()
{
	return sqrtf((x + x) + (y + y) + (z + z) + (w + w));
}

CQuaternion CQuaternion::Conjugate()
{
	return CQuaternion(-x , -y, -z, w);
}

CQuaternion CQuaternion::operator*(float s)
{
	return CQuaternion(x*s, y*s, z*s, w*s);
}

CQuaternion CQuaternion::Normalize()
{
	return *this * (1.0f/Measure());
}

CQuaternion CQuaternion::Rotation(CQuaternion & A, float theta)
{
	CQuaternion Axis = A - *this;
	Axis = Axis.Normalize();
	Axis = Axis*sinf(theta * 0.5f);
	Axis.w = cosf(theta * 0.5f);
	return Axis;
}

float CQuaternion::Dot(CQuaternion & A)
{
	return (x*A.x + y*A.y + z*A.z + w*A.w);
}

CQuaternion CQuaternion::Slerp(CQuaternion & B, float proportion)
{
	// Only unit CQuaternions are valid rotations.
	// Normalize to avoid undefined behavior.
	CQuaternion A = Normalize();
	B = B.Normalize();

	// Compute the cosine of the angle between the two vectors.
	float dot = A.Dot(B);

	const double DOT_THRESHOLD = 0.9995;
	if (fabs(dot) > DOT_THRESHOLD)
	{
		// If the inputs are too close for comfort, linearly interpolate
		// and normalize the result.

		CQuaternion result = A + (B - A)*proportion;
		return result.Normalize();
	}

	// If the dot product is negative, the CQuaternions
	// have opposite handed-ness and slerp won't take
	// the shorter path. Fix by reversing one CQuaternion.
	if (dot < 0.0f)
	{
		B = B*-1.0f;
		dot = -dot;
	}

	// Robustness: Stay within domain of acos()
	if (dot < -1.0f)
		dot = -1.0f;
	else if (dot > 1.0f)
		dot = 1.0f;

	// theta_0 = angle between input vectors
	float theta_0 = acosf(dot);
	// theta = angle between A and result 
	float theta = theta_0*proportion;

	// { A, v2 } is now an orthonormal basis
	CQuaternion v2 = B - A*dot;
	v2 = v2.Normalize();

	return A*cosf(theta) + v2*sinf(theta);
}