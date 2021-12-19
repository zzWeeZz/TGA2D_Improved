#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	myPosition = { 1280 * 0.5f, 720 * 0.5f };
	mySize = { 200, 200 };
	myRotation = 0;
	myColor = { 1, 1, 1, 1 };
	mySprite.Init(&myPosition, &mySize, &myRotation, &myColor);
}