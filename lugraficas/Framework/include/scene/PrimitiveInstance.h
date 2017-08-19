#ifndef PATO_PRIMITIVE_INSTANCE_H
#define PATO_PRIMITIVE_INSTANCE_H

#include "../Config.h"

#include <scene/PrimitiveBase.h>
#include <video/BaseDriver.h>
#include <CMatrix4D.h>

class PrimitiveInst
{
	public:
		void	CreateInstance(PrimitiveBase *pPrim, CMatrix4D *pVP)
		{
			pBase = pPrim;
			pViewProj = pVP;
			Position = Position.Identity();
			Scale = Position;
			RotationX = Position;
			RotationY = Position;
			RotationZ = Position;
			RotationZ = Position;
			Final = Position;
			Visible = true;
		}

		void	TranslateAbsolute(float x, float y, float z);
		void	TranslateAbsolute(CVector4D Translation);
		void	RotateXAbsolute(float ang);
		void	RotateYAbsolute(float ang);
		void	RotateZAbsolute(float ang);
		void	ScaleAbsolute(float sc);

		void	TranslateRelative(float x, float y, float z);
		void	RotateXRelative(float ang);
		void	RotateYRelative(float ang);
		void	RotateZRelative(float ang);
		void	ScaleRelative(float sc);

		void	SetSignature(unsigned int f);
		void	SetTexture(Texture* tex,int index);

		void	Update();
		void	Draw();

		void ToogleVisible() { Visible = !Visible; }
		void SetVisible(bool f) { Visible = f; }
		bool Visible;

		CMatrix4D		Position;
		CMatrix4D		Scale;
		CMatrix4D		RotationX;
		CMatrix4D		RotationY;
		CMatrix4D		RotationZ;
		CMatrix4D		Final;

		CMatrix4D		*pViewProj;

		PrimitiveBase	*pBase;
};


#endif
