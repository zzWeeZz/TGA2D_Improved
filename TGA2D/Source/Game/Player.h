#pragma once
#include "stdafx.h"
#include <vector>
#include <..\CommonUtilities\Vector.hpp>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/drawers/sprite_drawer.h>
#include <tga2d/texture/texture_manager.h>
#include <tga2d/engine.h>
#include <..\CommonUtilities\VectorOnStack.hpp>
#include <..\CommonUtilities\InputHandler.hpp>
#include "BulletFactory.h"
#include "EnemyFactory.h"

class Player
{
public:
	Player();	
	void Init(Tga2D::CColor aSpriteColor, CommonUtilities::Vector2<float> aParentPos, int aSpeed, EnemyFactory& aEnemyFac);
	Tga2D::CColor GetRandomColor();
	void Update(float aTimeDelta, CommonUtilities::InputHandler& aInputHandler);
	CommonUtilities::Vector2<float> GetPosition() const;
	void Render();
	~Player();
	EnemyFactory myEnemy;

private:
	CommonUtilities::Vector2<float> myPosition;
	int mySpeed;
	Tga2D::CTexture* myTexture;
	Tga2D::CColor myColor;
	BulletFactory myBulletFactory;
};
