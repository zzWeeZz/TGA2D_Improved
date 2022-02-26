#pragma once
#include "stdafx.h"
#include <..\CommonUtilities\Vector2.hpp>

#include "../../Threading/RenderCommander.h"

class Sprite
{
public:
	void Init(const char* aSpritePath, const Vector2f& aPosition = Vector2f(100, 100), const Vector2f& aSizeMultiplier = Vector2f(1, 1));
	void GiveTexture(Tga2D::CTexture* aTexture);
	void SetPosition(const Vector2f& aPosition);
	[[nodiscard]] Vector2f GetPosition() const;
	LogicData<DataType::Sprite>& GetSpriteData();
	void Render(const RenderCommander* aRenderCommander) const;
private:
	LogicData<DataType::Sprite> myData;
};
