#ifndef PATO_D3DXRT_H
#define PATO_D3DXRT_H

#include "../Config.h"

#include <video/BaseDriver.h>
#include <video/D3DXTexture.h>

#include <d3d11.h>
#include <dxgi.h>
#include <vector>

#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

class D3DXRT : public BaseRT
{
	public:
		bool LoadAPIRT();
		void DestroyAPIRT();

		std::vector<ComPtr<ID3D11RenderTargetView>>		vD3D11RenderTargetView;
		std::vector<ComPtr<ID3D11Texture2D>>			vD3D11ColorTex;		
		ComPtr<ID3D11Texture2D>							D3D11DepthTex;
		ComPtr<ID3D11DepthStencilView>					D3D11DepthStencilTargetView;
};

#endif