#include "stdafx.h"
#include "Character.h"

#include "tga2d/d3d/direct_3d.h"
#include "tga2d/drawers/sprite_drawer.h"
#include "tga2d/sprite/sprite.h"
#include "tga2d/texture/texture_manager.h"
#include <iostream>

void Character::Init()
{
	myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("Sprites/square.dds");
}

void Character::Update(float aTimeDelta, const CommonUtilities::InputHandler& aInputHandler)
{
	if(aInputHandler.KeyIsPressed(myLeftKey))
	{
		myPosition.x -= 100 * aTimeDelta;
	}
	if(aInputHandler.KeyIsPressed(myRightKey))
	{
		myPosition.x += 100 * aTimeDelta;
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
	spriteInstance.mySize = { mySize.x / resolution.myX, mySize.y / resolution.myY };
	spriteInstance.myRotation = 0;
	spriteInstance.myColor = myColor;

	spriteDrawer.Draw(sharedData, spriteInstance);
}
