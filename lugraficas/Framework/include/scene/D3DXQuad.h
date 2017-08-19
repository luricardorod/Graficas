#ifndef PATO_QUAD_D3DX_H
#define PATO_QUAD_D3DX_H

#include "../Config.h"

#include <video\BaseDriver.h>
#include <video\D3DXTexture.h>
#include <CMatrix4D.h>
#include <scene\PrimitiveBase.h>

class D3DXQuad : public PrimitiveBase
{
public:
	struct CBuffer
	{
		simplefloat16 WVP;
		simplefloat16 World;
		simplefloat16 WorldView;
		simplefloat16 WVPInverse;
		simplefloat16 WVPLight;
		simplefloat4 LightPositions[128];
		simplefloat4 LightColors[128];
		simplefloat4 CameraPos;
		simplefloat4 CameraInfo;		
		simplefloat4 LightCameraPos;
		simplefloat4 LightCameraInfo;
	};

	D3DXQuad() {}
	void Create();
	void Create(char *) {}
	void Transform(CMatrix4D * t);
	void Draw(CMatrix4D * t, CMatrix4D * vp);
	void Destroy();

	unsigned int	SigBase;

	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;
	ComPtr<ID3D11SamplerState>  pSampler;

	CBuffer			CnstBuffer;
	CVertex			vertices[4];
	unsigned short	indices[6];

	CMatrix4D		transform;
	

	D3DXTexture*	d3dxTextures[8];

};

#endif