#include "stdafx.h"

#include "Sprite.h"

#include "tga2d/d3d/direct_3d.h"
#include "tga2d/drawers/sprite_drawer.h"
#include "tga2d/sprite/sprite.h"
#include "tga2d/texture/texture_manager.h"

void Sprite::Init(const char* aSpritePath, const Vector2f& aPosition, const Vector2f& aSizeMultiplier)
{
 	myData.myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(aSpritePath);
	myData.myPosition = aPosition;
	myData.mySizeMultiplier = aSizeMultiplier;
}

void Sprite::GiveTexture(Tga2D::CTexture* aTexture)
{
	myData.myTexture = aTexture;
}

void Sprite::SetPosition(const Vector2f& aPosition)
{
	myData.myPosition = aPosition;
}

LogicData<DataType::Sprite>& Sprite::GetSpriteData()
{
	return myData;
}

Vector2f Sprite::GetPosition() const
{
	return myData.myPosition;
}

void Sprite::Render(const RenderCommander* aRenderCommander) const
{
	aRenderCommander->AddRenderCommand(myData);
}
