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
#include "Threading/RenderCommander.h"
#include "Threading/RenderData.hpp"


CGameWorld::CGameWorld()
{
}

CGameWorld::~CGameWorld()
{
}
void CGameWorld::Init()
{
	myLogicData.myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("square.dds");
}

void CGameWorld::Update(float aTimeDelta, float aTotalTime, CommonUtilities::InputHandler& aInputHandler)
{
	aTimeDelta;
	aTotalTime;
	aInputHandler;
	myLogicData.myPosition.x += aTimeDelta;
}

void CGameWorld::Render(RenderCommander* aRenderCommander)
{
	aRenderCommander->AddRenderCommand(std::make_shared <LogicData>(myLogicData));
}
