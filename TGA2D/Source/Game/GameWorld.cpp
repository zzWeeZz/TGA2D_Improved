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
	myText = new Tga2D::CText();
	myEnemies.Init();
	myPlayer.Init({ 1,1 , 0, 1 }, { 640, 360 }, 250, myEnemies);
}

void CGameWorld::Update(float aTimeDelta, float aTotalTime, CommonUtilities::InputHandler& aInputHandler)
{
	myText->SetPosition({ 0.5f, 0.5f});
	myText->SetText("wellcome to space invaders press space To Start");
	if(aInputHandler.GetKeyDown(VK_SPACE))
	{
		myPlayGmae = true;
	}
	if (myPlayGmae)
	{

		aTimeDelta;
		aInputHandler;
		myEnemies.Update(aTimeDelta);
		myPlayer.Update(aTimeDelta, aInputHandler);
		if(myPlayer.myEnemy.Stop())
		{
			myText->SetText("game over");
			myPlayGmae = true;
			
		}
	}
}

void CGameWorld::Render()
{
	myEnemies.Render();
	if(!myPlayGmae)
	{
		myText->Render();
	}
	myPlayer.Render();
}
