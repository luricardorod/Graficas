#include <utils/Camera.h>

#define RHMODE
#ifdef LHMODE
void TransformNormal(CVector4D & vpout, const CVector4D & v, const CMatrix4D & mat)
{
	vpout.x = v.x*mat.m[0][0] + v.y*mat.m[1][0] + v.z*mat.m[2][0];
	vpout.y = v.x*mat.m[0][1] + v.y*mat.m[1][1] + v.z*mat.m[2][1];
	vpout.z = v.x*mat.m[0][2] + v.y*mat.m[1][2] + v.z*mat.m[2][2];
	vpout.w = 1.0f;
}
#elif defined (RHMODE)
void TransformNormal(CVector4D & vpout, const CVector4D & v, const CMatrix4D & mat)
{
	vpout.x = v.x*mat.m[0][0] + v.y*mat.m[0][1] + v.z*mat.m[0][2];
	vpout.y = v.x*mat.m[1][0] + v.y*mat.m[1][1] + v.z*mat.m[1][2];
	vpout.z = v.x*mat.m[2][0] + v.y*mat.m[2][1] + v.z*mat.m[2][2];
	vpout.w = 1.0f;
}
#endif

Camera::Camera()
{
	Reset();
}

void Camera::Init(CVector4D position, float fov, float ratio, float np, float fp, bool lf)
{
	this->Fov = fov;
	this->AspectRatio = ratio;
	this->NPlane = np;
	this->FPlane = fp;
	this->Eye = position;

	CreatePojection();
}

void Camera::CreatePojection()
{
	Projection = Projection.PerspectiveFov(Fov, AspectRatio, NPlane, FPlane);
}

void Camera::SetFov(float f)
{
	this->Fov = f;
	CreatePojection();
}

void Camera::SetRotation(float rotateX, float rotateY, float rotateZ)
{
	Rotater = Rotater.RotationX(rotateX)*Rotater.RotationY(rotateY)*Rotater.RotationZ(rotateZ);
	LocalForward = CVector4D(0, 0, 1, 0)*Rotater;
	LocalRight = CVector4D(1, 0, 0, 0)*Rotater;
	LocalUp = CVector4D(0, 1, 0, 0)*Rotater;

	LocalForward.w = 0;
	LocalRight.w = 0;
	LocalUp.w = 0;

	LocalForward.Normalize();
	LocalRight.Normalize();
	LocalUp.Normalize();
}

void Camera::SetRatio(float r)
{
	this->AspectRatio = r;
	CreatePojection();
}

void Camera::SetPlanes(float n, float f)
{
	this->NPlane = n;
	this->FPlane = f;
	CreatePojection();
}

void Camera::Move(float locForward, float locUp, float locRight)
{
	Eye = Eye + LocalForward*locForward + LocalUp*locUp + LocalRight*locRight;
}

void Camera::Update()
{
	CVector4D LookAt = Eye + LocalForward.Normalize()*2.0f;
	View = View.LookAtRH(Eye, LookAt, LocalUp);
	VP = View*Projection;
}

void Camera::Reset()
{
	Eye = CVector4D(0.0f, 0.0f, 0.0f, 1.0f);

	Fov = Deg2Rad*45.0f;
	NPlane = 0.01f;
	FPlane = 1000.0f;
	AspectRatio = 1.0f;

	LocalForward = CVector4D(0.0f, 0.0f, 1.0f, 0.0f);
	LocalUp = CVector4D(0.0f, 1.0f, 0.0f, 0.0f);
	LocalRight = CVector4D(1.0f, 0.0f, 0.0f, 0.0f);

	m_fYaw = 0.0f;
	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
}