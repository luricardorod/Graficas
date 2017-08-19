#ifndef PATO_MESH_D3D_H
#define PATO_MESH_D3D_H

#include "../Config.h"

#include <video\D3DXTexture.h>
#include <D3Dcompiler.h>

#include <video\BaseDriver.h>

#include <utils\Utils.h>

#include <CMatrix4D.h>
#include <scene\PrimitiveBase.h>

#include <vector>

struct MeshBone
{
	std::string Name;
	CMatrix4D m_CMat4Relative;
	int m_iParent;
	std::vector<int> m_vecChildren;
	std::vector<int> m_vecSiblings;
};

struct SAnimation
{
	std::string Name;
	std::vector <CQuaternion> Scalation;
	std::vector <int> ScalationTimes;
	std::vector <CQuaternion> Rotation;
	std::vector <int> RotationTimes;
	std::vector <CQuaternion> Traslation;
	std::vector <int> TraslationTimes;
};

struct SAnimationSet
{
	std::string Name;
	std::vector <SAnimation> Keys;
};

class D3DXMesh : public PrimitiveBase
{
public:
	D3DXMesh() {};
	~D3DXMesh() {};
	void Create() {}
	void Create(char * filename);
	void Transform(CMatrix4D * t);
	void Draw(CMatrix4D * t, CMatrix4D * vp);
	void Destroy();

	bool D3DXMesh::LoadMeshBone(int myFather, char * g_Line, const char * cFile, const long fileSz, long & OriginalStartPosition, long & OriginalEndPosition);

	struct CBuffer
	{
		simplefloat16 WVP;
		simplefloat16 World;
		simplefloat16 WorldView;
		simplefloat4 Light0Pos;
		simplefloat4 Light0Col;
		simplefloat4 CameraPos;
		simplefloat4 CameraInfo;
		simplefloat4 Ambient;
	};

	std::vector<ComPtr<ID3D11Buffer>>	IB;
	std::vector<ComPtr<ID3D11Buffer>>	WIB;
	ComPtr<ID3D11Buffer>				VB;
	ComPtr<ID3D11VertexShader>			pVS;
	ComPtr<ID3D11PixelShader>			pFS;
	ComPtr<ID3DBlob>					VS_blob;
	ComPtr<ID3DBlob>					FS_blob;
	ComPtr<ID3D11InputLayout>			Layout;
	ComPtr<ID3D11Buffer>				pd3dConstantBuffer;

	D3DXMesh::CBuffer	CnstBuffer;

	CVertex *verticesOriginales;
	CVertex *vertices;
	int verticesSz;
	std::vector<std::vector<unsigned short>> indices;
	std::vector<std::vector<unsigned short>> wireframeIndex;

	std::vector<MeshBone> Bones;
	std::vector<SAnimationSet> Animations;

	CMatrix4D transform;

	int Sig;

	bool hasNormals;
	bool hasBiNormals;
	bool hasTangets;
	bool hasUVs;
	bool hasDifusse;
	bool hasSpecular;
	bool hasGlossMap;
	bool hasNormalMap;

	std::vector<int> TextureID;
	std::vector<int> NormalMapID;
	std::vector<int> SpecularMapID;
	std::vector<int> GlossMapID;

	std::vector<bool> useTexture;
	std::vector<bool> useNormalMap;
	std::vector<bool> useSpecularMap;
	std::vector<bool> useGlossMap;

	std::vector<Texture*> Textures;

	std::string file_name;
private:
	bool needToLoadAnimation;
};

#endif