#include <scene/PrimitiveInstance.h>

void PrimitiveInst::TranslateAbsolute(float x, float y, float z)
{
	Position = Position.Translation(x, y, z);
}

void PrimitiveInst::TranslateAbsolute(CVector4D Translation)
{
	Position = Position.Translation(Translation.x, Translation.y, Translation.z);
}

void PrimitiveInst::RotateXAbsolute(float ang)
{
	RotationX = RotationX.RotationX(Deg2Rad*ang);
}

void PrimitiveInst::RotateYAbsolute(float ang)
{
	RotationY = RotationY.RotationY(Deg2Rad*ang);
}

void PrimitiveInst::RotateZAbsolute(float ang)
{
	RotationZ = RotationZ.RotationZ(Deg2Rad*ang);
}

void PrimitiveInst::ScaleAbsolute(float sc)
{
	Scale = Scale.Scaling(sc,sc,sc);
}

void PrimitiveInst::TranslateRelative(float x, float y, float z)
{
	CMatrix4D tmp;
	tmp = tmp.Translation(x, y, z);
	Position *= tmp;
}

void PrimitiveInst::RotateXRelative(float ang)
{
	CMatrix4D tmp;
	tmp = tmp.RotationX(Deg2Rad*ang);
	RotationX *= tmp;
}

void PrimitiveInst::RotateYRelative(float ang)
{
	CMatrix4D tmp;
	tmp = tmp.RotationY(Deg2Rad*ang);
	RotationY *= tmp;
}

void PrimitiveInst::RotateZRelative(float ang)
{
	CMatrix4D tmp;
	tmp = tmp.RotationZ(Deg2Rad*ang);
	RotationZ *= tmp;
}

void PrimitiveInst::ScaleRelative(float sc)
{
	CMatrix4D tmp;
	tmp = tmp.Scaling(sc, sc, sc);
	Scale *= tmp;
}

void PrimitiveInst::Update()
{
	Final = Scale*RotationX*RotationY*RotationZ*Position;
}

void PrimitiveInst::Draw()
{
	if (!Visible)
		return;
	pBase->Draw(&Final, pViewProj);
}

void PrimitiveInst::SetSignature(unsigned int f)
{
	pBase->SetGlobalSignature(f);
}

void PrimitiveInst::SetTexture(Texture* tex, int index)
{
	pBase->SetTexture(tex,index);
}
