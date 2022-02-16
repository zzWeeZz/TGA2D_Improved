#include "stdafx.h"

#include "Sprite.h"

#include "tga2d/d3d/direct_3d.h"
#include "tga2d/drawers/sprite_drawer.h"
#include "tga2d/sprite/sprite.h"
#include "tga2d/texture/texture_manager.h"

void Sprite::Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, float* aRotation, Tga2D::CColor* aColor)
{
	myPosition = aPosition;
	mySize = aSize;
	myRotation = aRotation;
	myColor = aColor;
}

void Sprite::GiveSpritePath(const char* aSpritePath)
{
	myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(aSpritePath);
}

void Sprite::GiveTexture(Tga2D::CTexture* aTexture)
{
	myTexture = aTexture;
}

void Sprite::Render()
{
	const auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	Tga2D::CSpriteDrawer& spriteDrawer(Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer());
	Tga2D::SSpriteSharedData sharedData = {};
	sharedData.myTexture = myTexture;

	Tga2D::SSpriteInstanceData spriteInstance = {};
	spriteInstance.myPivot = { 0.5f, 0.5f };
	spriteInstance.myPosition = { myPosition->x / resolution.myX, myPosition->y / resolution.myY };
	spriteInstance.mySize = { mySize->x / resolution.myY, mySize->y / resolution.myY };
	spriteInstance.myRotation = *myRotation;
	spriteInstance.myColor = *myColor;

	spriteDrawer.Draw(sharedData, spriteInstance);
}

Sprite::~Sprite()
{
	myTexture = nullptr;
	myPosition = nullptr;
	mySize = nullptr;
	myRotation = nullptr;
	myColor = nullptr;
	delete myTexture;
	delete myPosition;
	delete mySize;
	delete myRotation;
	delete myColor;
}
