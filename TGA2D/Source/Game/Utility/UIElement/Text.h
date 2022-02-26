#pragma once
#include "../../Threading/RenderCommander.h"

class Text
{
public:
	void CreateText(const char* aFontPath, const char* aContent, Tga2D::EFontSize aFontSize, const Vector2f& aPosition = Vector2f(100, 100));
	void SetPosition(const Vector2f& aPosition) const;
	void SetColor(const Vector4f& aColor) const;
	void Render(const RenderCommander* aRenderCommander) const;
private:
	LogicData<DataType::Text> myData;
};
