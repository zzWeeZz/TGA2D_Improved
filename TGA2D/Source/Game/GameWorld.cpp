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


CGameWorld::CGameWorld() : myCharacterOne(VK_LEFT, VK_RIGHT, &myCharacterTwo.myCollider),
						   myCharacterTwo(A_KEY, D_KEY, &myCharacterOne.myCollider)
{
}

CGameWorld::~CGameWorld()
{
}
void CGameWorld::Init()
{
	
}

void CGameWorld::Update(float aTimeDelta, float aTotalTime, CommonUtilities::InputHandler& aInputHandler)
{
	aTimeDelta;
	aTotalTime;
	aInputHandler;
	myCharacterOne.Update(aTimeDelta, aInputHandler);
	myCharacterTwo.Update(aTimeDelta, aInputHandler);
}

void CGameWorld::Render()
{
	myCharacterOne.Render();
	myCharacterTwo.Render();
}
