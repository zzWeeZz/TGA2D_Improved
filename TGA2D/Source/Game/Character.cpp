#include "stdafx.h"
#include "Character.h"

#include "tga2d/d3d/direct_3d.h"
#include "tga2d/drawers/sprite_drawer.h"
#include "tga2d/sprite/sprite.h"
#include "tga2d/texture/texture_manager.h"
#include <iostream>


void Character::Init(int aLeftKey, int aRightKey, int aUpKey, int aDownKey, bool aCircle)
{

	myIsCircle = aCircle;
	if (aCircle)
	{
		mySprite.GiveSpritePath("Sprites/circle.dds");
		myCircleCollider.Init(&myPosition, &mySize, myCircleCollider);
	}
	else
	{
		mySprite.GiveSpritePath("Sprites/square.dds");
		myBoxCollider.Init(&myPosition, &mySize, myBoxCollider);
	}
	myLeftKey = aLeftKey;
	myRightKey = aRightKey;
	myUpKey = aUpKey;
	myDownKey = aDownKey;
}
void Character::Update(float aTimeDelta, const CommonUtilities::InputHandler& aInputHandler)
{
	if (aInputHandler.KeyIsPressed(myLeftKey))
	{
		myPosition.x -= 100 * aTimeDelta;
	}
	if (aInputHandler.KeyIsPressed(myRightKey))
	{
		myPosition.x += 100 * aTimeDelta;
	}
	if (aInputHandler.KeyIsPressed(myUpKey))
	{
		myPosition.y -= 100 * aTimeDelta;
	}
	if (aInputHandler.KeyIsPressed(myDownKey))
	{
		myPosition.y += 100 * aTimeDelta;
	}
	if (myIsCircle)
	{
		if (myCircleCollider.HasCollided())
		{
			myColor = { 0, 1, 1, 1 };
		}
		else
		{
			myColor = { 1, 1, 1, 1 };
		}
	}
	else
	{
		if (myBoxCollider.HasCollided())
		{
			myColor = { 0.5, 0, 0.5, 1 };
		}
		else
		{
			myColor = { 1, 1, 1, 1 };
		}
	}

}

void Character::Render()
{
	mySprite.Render();
}

void Character::DelegateCall()
{
	std::cout << "holy shit it worked\n";
}
