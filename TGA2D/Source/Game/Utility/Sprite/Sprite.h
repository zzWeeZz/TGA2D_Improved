#pragma once
#include "stdafx.h"
#include <..\CommonUtilities\Vector2.hpp>

class Sprite
{
public:
	void Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, float* aRotation, Tga2D::CColor* aColor);
	void GiveSpritePath(const char* aSpritePath);
	void GiveTexture(Tga2D::CTexture* aTexture);
	void Render();
	~Sprite();
private:
	Tga2D::CTexture* myTexture;
	CommonUtilities::Vector2<float>* myPosition;
	CommonUtilities::Vector2<float>* mySize;
	float* myRotation;
	Tga2D::CColor* myColor;
};