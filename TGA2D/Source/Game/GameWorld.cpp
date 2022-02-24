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
	for (int i = 0; i < 100; ++i)
	{
		LogicData<DataType::Sprite> data;
		data.myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("Sprites/tga_logo.dds");
		data.myPosition.y = 350;
		myLogicData.emplace_back(data);
	}
	for (int i = 0; i < 100; ++i)
	{
		LogicData<DataType::Sprite> data;
		data.myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("Sprites/tga_logo2.dds");
		data.mySizeMultiplier = { 0.5f, 0.5f };
		data.myColor = { 0,1, 0, 1 };
		data.myPosition.y = 350;
		myOtherLogicData.emplace_back(data);
	}
	myText.myText = new Tga2D::CText();
	myText.myText->SetText("hej!");
	myText.myText->SetPosition({0.5f, 0.5f});
	myOtherValue = 1;
	myValue = 1;
}

void CGameWorld::Update(float aTimeDelta, float aTotalTime, CommonUtilities::InputHandler& aInputHandler)
{
	aTimeDelta;
	aTotalTime;
	aInputHandler;
	for (auto& element : myLogicData)
	{

		element.myPosition.x += myValue * aTimeDelta * 500;
		if (element.myPosition.x >= 1000)
		{
			myValue = -1;
		}
		else if (element.myPosition.x <= 250)
		{
			myValue = 1;
		}
	}
	for (auto& element : myOtherLogicData)
	{

		element.myPosition.y += myOtherValue * aTimeDelta * 500;
		element.myRotation += aTimeDelta * 10;
		if (element.myPosition.y >= 720)
		{
			myOtherValue = -1;
		}
		else if (element.myPosition.y <= 0)
		{
			myOtherValue = 1;
		}
	}
}

void CGameWorld::Render(const RenderCommander* aRenderCommander)
{
	aRenderCommander->AddRenderCommand(myLogicData);
	aRenderCommander->AddRenderCommand(myOtherLogicData);
	aRenderCommander->AddRenderCommand(myText);
}
