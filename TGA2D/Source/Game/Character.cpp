#include "stdafx.h"
#include "Character.h"

#include "tga2d/d3d/direct_3d.h"
#include "tga2d/drawers/sprite_drawer.h"
#include "tga2d/sprite/sprite.h"
#include "tga2d/texture/texture_manager.h"
#include <iostream>

Character::Character() : myCircleCollider(myCircleCollider)
{
}

void Character::Init(int aLeftKey, int aRightKey, int aUpKey, int aDownKey, bool aCircle)
{
	myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("Sprites/circle.dds");
	myPosition = { 1280 / 2, 720 / 2 };
	mySize = { 100, 100 };
	myIsCircle = aCircle;
	if (aCircle)
		myCircleCollider.Init(&myPosition, &mySize, myCircleCollider);
	else
		myBoxCollider.Init(&myPosition, &mySize, myBoxCollider);
	myLeftKey = aLeftKey;
	myRightKey = aRightKey;
	myUpKey = aUpKey;
	myDownKey = aDownKey;
	myColor = { 1, 1, 1, 1 };

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
		if (myCircleCollider.hasCollided())
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
		if(myBoxCollider.HasCollided())
		{
			myColor = { 0, 1, 1, 1 };
		}
		else
		{
			myColor = { 1, 1, 1, 1 };
		}
	}

}

void Character::Render()
{
	const auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	Tga2D::CSpriteDrawer& spriteDrawer(Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer());
	Tga2D::SSpriteSharedData sharedData = {};
	sharedData.myTexture = myTexture;

	Tga2D::SSpriteInstanceData spriteInstance = {};
	spriteInstance.myPivot = { 0.5f, 0.5f };
	spriteInstance.myPosition = { myPosition.x / resolution.myX, myPosition.y / resolution.myY };
	spriteInstance.mySize = { mySize.x / resolution.myY, mySize.y / resolution.myY };
	spriteInstance.myRotation = 0;
	spriteInstance.myColor = myColor;

	spriteDrawer.Draw(sharedData, spriteInstance);
}

void Character::DelegateCall()
{
	std::cout << "holy shit it worked\n";
}
