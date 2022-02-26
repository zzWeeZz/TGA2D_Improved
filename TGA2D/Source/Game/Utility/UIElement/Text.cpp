#include "stdafx.h"
#include "Text.h"

void Text::CreateText(const char* aFontPath, const char* aContent, Tga2D::EFontSize aFontSize, const Vector2f& aPosition)
{
	myData.myText = new Tga2D::CText(aFontPath, aFontSize);
	myData.myText->SetPosition({ aPosition.x, aPosition.y });
}

void Text::SetPosition(const Vector2f& aPosition) const
{
	myData.myText->SetPosition({ aPosition.x, aPosition.y });
}

void Text::SetColor(const Vector4f& aColor) const
{
	myData.myText->SetColor({ aColor.x, aColor.y, aColor.z, aColor.w });
}

void Text::Render(const RenderCommander* aRenderCommander) const
{
	aRenderCommander->AddRenderCommand(myData);
}
