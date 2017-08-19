#include <video/D3DXRT.h>
#include <iostream>

extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;

bool D3DXRT::LoadAPIRT()
{
	DXGI_FORMAT cfmt;
	DXGI_FORMAT depthFormat,depthShaderViewFormat,depthResourceViewFormat;
	
	switch (this->color_format)
	{
		case BaseRT::NOTHING:
		{
			cfmt = DXGI_FORMAT_R8G8B8A8_UNORM;
			number_RT = 0;
		}
		break;
		case BaseRT::RGB8:
		case BaseRT::RGBA8:
		{
			cfmt = DXGI_FORMAT_R8G8B8A8_UNORM;
		}
		break;
		case BaseRT::RGBA16F:
		{
			cfmt = DXGI_FORMAT_R16G16B16A16_FLOAT;
		}
		break;
		case BaseRT::RGBA32F:
		{
			cfmt = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
		break;
	}

	switch (this->depth_format)
	{
		case BaseRT::NOTHING:
		{
			depthFormat = DXGI_FORMAT_R32_TYPELESS;
			depthShaderViewFormat = DXGI_FORMAT_D32_FLOAT;
			depthResourceViewFormat = DXGI_FORMAT_R32_FLOAT;
		}
		break;
		case BaseRT::FD16:
		{
			depthFormat = DXGI_FORMAT_R16_TYPELESS;
			depthShaderViewFormat = DXGI_FORMAT_D16_UNORM;
			depthResourceViewFormat = DXGI_FORMAT_R16_FLOAT;
		}
		break;
		case BaseRT::F32:
		{
			depthFormat = DXGI_FORMAT_R32_TYPELESS;
			depthShaderViewFormat = DXGI_FORMAT_D32_FLOAT;
			depthResourceViewFormat = DXGI_FORMAT_R32_FLOAT;
		}
		break;
	}

	HRESULT hr;
	for (int i = 0; i < number_RT; i++)
	{
		D3D11_TEXTURE2D_DESC desc = { 0 };
		desc.Width = w;
		desc.Height = h;
		desc.ArraySize = 1;
		desc.Format = cfmt;
		desc.SampleDesc.Count = 1;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.MipLevels = 1;
		ComPtr<ID3D11Texture2D> Tex;
		hr = D3D11Device->CreateTexture2D(&desc, nullptr, Tex.GetAddressOf());
		if (hr != S_OK)
		{
			std::cout << "Error loading RT texture index " << i << std::endl;
			exit(444);
		}
		vD3D11ColorTex.push_back(Tex);
		D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
		ZeroMemory(&rtDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtDesc.Format = desc.Format;
		ComPtr<ID3D11RenderTargetView> RTV;
		hr = D3D11Device->CreateRenderTargetView(Tex.Get(), &rtDesc, &RTV);
		if (hr != S_OK)
		{
			std::cout << "Error creating RTV index " << i << std::endl;
			exit(444);
		}
		vD3D11RenderTargetView.push_back(RTV);

		D3DXTexture *pTextureColor = new D3DXTexture;
		pTextureColor->Tex = Tex;

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		shaderResourceViewDesc.Format = cfmt;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		hr = D3D11Device->CreateShaderResourceView(Tex.Get(), &shaderResourceViewDesc, &pTextureColor->pSRVTex);
		if (hr != S_OK)
		{
			delete pTextureColor;
			std::cout << "Error creating Shader Resource View index" << i << std::endl;
			exit(444);
		}
		vColorTextures.push_back(pTextureColor);
	}

	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = w;
	descDepth.Height = h;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = depthFormat;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = D3D11Device->CreateTexture2D(&descDepth, NULL, &D3D11DepthTex);
	if (hr != S_OK)
	{
		std::cout << "Error loading RT depth texture " << std::endl;
		exit(444);
	}
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = depthShaderViewFormat;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	hr = D3D11Device->CreateDepthStencilView(D3D11DepthTex.Get(), &dsvd, &D3D11DepthStencilTargetView);
	if (hr != S_OK)
	{
		std::cout << "Error creating Depth Stencil View " << std::endl;
		exit(444);
	}

	D3DXTexture *pTextureDepth = new D3DXTexture;
	pTextureDepth->Tex = D3D11DepthTex;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = depthResourceViewFormat;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	hr = D3D11Device->CreateShaderResourceView(D3D11DepthTex.Get(), &shaderResourceViewDesc, &pTextureDepth->pSRVTex);
	if (hr != S_OK)
	{
		delete pTextureDepth;
		std::cout << "Error creating Shader Resource View Depth " << std::endl;
		exit(444);
	}
	pDepthTexture = pTextureDepth;

	return true;
}

void D3DXRT::DestroyAPIRT()
{

}