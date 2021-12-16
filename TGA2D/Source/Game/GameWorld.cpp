#include "stdafx.h"
#include "GameWorld.h"
#include <iostream>
#include <tga2d/engine.h>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/drawers/sprite_drawer.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/texture/texture_manager.h>

#include "tga2d/text/text.h"


CGameWorld::CGameWorld()
{
}

CGameWorld::~CGameWorld()
{
}
void CGameWorld::Init()
{
	myCharacter.Init(VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, true);
	myCharacterTwo.Init(A_KEY, D_KEY, W_KEY, S_KEY, false);
}

void CGameWorld::Update(float aTimeDelta, float aTotalTime, CommonUtilities::InputHandler& aInputHandler)
{
	aTimeDelta;
	aTotalTime;
	aInputHandler;
	myCharacter.Update(aTimeDelta, aInputHandler);
	myCharacterTwo.Update(aTimeDelta, aInputHandler);
}

void CGameWorld::Render()
{
	myCharacter.Render();

	myCharacterTwo.Render();
	
}
