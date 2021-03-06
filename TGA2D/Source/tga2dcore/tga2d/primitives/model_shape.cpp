#include "stdafx.h"
#include <tga2d/primitives/model_shape.h>
#include <tga2d/engine.h>
#include <tga2d/render/Renderer.h>
#include <tga2d/texture/texture_manager.h>
#include <tga2d/loaders/FBXLoader.h>
#include <tga2d/shaders/shader.h>
#include <tga2d/shaders/shader_model.h>

using namespace Tga2D;
CModelShape::CModelShape()
{}

CModelShape::~CModelShape()
{}

bool CModelShape::Init(CLoaderMesh* aModel)
{
	myIndexCount = static_cast<unsigned int>(aModel->myIndexes.size());
	HRESULT hr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.ByteWidth = aModel->myVertexBufferSize * aModel->myVertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = aModel->myVertexBufferSize;
	myVertexStride = bd.StructureByteStride;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	InitData.pSysMem = &aModel->myVertices[0];

	hr = CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateBuffer(&bd, &InitData, myVertexBuffer.ReleaseAndGetAddressOf());
	if (FAILED(hr) != S_OK)
		return false;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.ByteWidth = sizeof(unsigned int) * static_cast<unsigned int>(aModel->myIndexes.size());
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	ZeroMemory(&InitData, sizeof(InitData));

	InitData.pSysMem = &aModel->myIndexes[0];

	hr = CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateBuffer(&bd, &InitData, myIndexBuffer.ReleaseAndGetAddressOf());
	if (FAILED(hr) != S_OK)
		return false;


	myShader = std::make_unique<CShaderModel>(CEngine::GetInstance());
	myShader->Init();

	return true;
}

void Tga2D::CModelShape::Render(std::vector<CTexture*>& myTextures, Matrix44* someBones, VECTOR2F aPosition, float aRotation, VECTOR2F aScale, bool aIsFlipped)
{
	myFrameByFrameData.myFrameByFrameBones = someBones;
	myFrameByFrameData.myPosition = aPosition;
	myFrameByFrameData.myRotation = aRotation;
	myFrameByFrameData.myScale = aScale;
	myFrameByFrameData.myIsFlippedX = aIsFlipped;

	CEngine::GetInstance()->GetDirect3D().Set3DRenderState();
	if (myTextures.size() > 0 )
	{
		const int textureCount = 1 + EShaderMap::MAP_MAX;
		ID3D11ShaderResourceView* textures[textureCount];
		textures[0] = myTextures[0]->myResource.Get();
		if (myTextures.size() > 1)
			textures[1] = myTextures[1]->myResource.Get();
		else
			textures[1] = CEngine::GetInstance()->GetTextureManager().GetDefaultNormalMapResource();

		CEngine::GetInstance()->GetDirect3D().GetContext()->PSSetShaderResources(4, textureCount, textures);
	}

	CEngine::GetInstance()->GetDirect3D().SetSamplerState(ESamplerFilter::Point, ESamplerAddressMode::Wrap);
	CEngine::GetInstance()->GetRenderer().AddToRender(this);
	CEngine::GetInstance()->GetDirect3D().Set2DRenderState();
}

void CModelShape::Draw(CDirectEngine* /*aRenderer*/)
{
	myShader->Render(this, myVertexBuffer.Get(), myIndexBuffer.Get(), myOffsetPosition, myOffsetRotation);
}