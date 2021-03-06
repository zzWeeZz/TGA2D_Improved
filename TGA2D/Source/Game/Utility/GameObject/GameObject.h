#pragma once
#include "..\Sprite\Sprite.h"

class GameObject
{
public:
	GameObject();
protected:
	Sprite mySprite;
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> mySize;
	float myRotation;
	Tga2D::CColor myColor;
};