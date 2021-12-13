#include "stdafx.h"
#include "Player.h"
#include <UtilityFunctions.hpp>

#include "InputHandler.hpp"

#define SCREEN_SIZE_X static_cast<float>(Tga2D::CEngine::GetInstance()->GetTargetSize().myX)
#define SCREEN_SIZE_Y static_cast<float>(Tga2D::CEngine::GetInstance()->GetTargetSize().myY)
#define CONVERTER(a) Tga2D::Vector2f(a.x, a.y)

Player::Player() = default;

void Player::Init(Tga2D::CColor aSpriteColor, CommonUtilities::Vector2<float> aParentPos, int aSpeed, EnemyFactory & aEnemyFac)
{
	myEnemy = aEnemyFac;
	mySpeed = aSpeed;
	myColor = aSpriteColor;
	myPosition = CommonUtilities::Vector2(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - 100);
	myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("sprites/Player.dds");
	
}

Tga2D::CColor Player::GetRandomColor()
{
	return { 1.f, 0.f, 0.5f, 1 };
}

void Player::Update(float aTimeDelta, CommonUtilities::InputHandler & aInputHandler)
{
	aTimeDelta;
	if (aInputHandler.KeyIsPressed(VK_RIGHT))
	{
		myPosition.x += mySpeed * aTimeDelta;
	}
	if (aInputHandler.KeyIsPressed(VK_LEFT))
	{
		myPosition.x -= mySpeed * aTimeDelta;
	}
	if(aInputHandler.GetKeyDown(VK_SPACE))
	{
		myBulletFactory.FireBullet(Vec2F(0, -1), myPosition);
	}
	myBulletFactory.Update(aTimeDelta);
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 6; ++i)
		{
			myBulletFactory.DetectHit(myEnemy.GetEnemy(j, i));
		}
	}
	myPosition.x = CommonUtilities::Clamp(myPosition.x, 100.f, SCREEN_SIZE_X - 100);
}


CommonUtilities::Vector2<float> Player::GetPosition() const
{
	return myPosition;
}


void Player::Render()
{
	auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	Tga2D::CSpriteDrawer& spriteDrawer(Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer());
	Tga2D::SSpriteSharedData sharedData = {};
	sharedData.myTexture = myTexture;

	Tga2D::SSpriteInstanceData spriteInstance = {};
	spriteInstance.myPivot = { 0.35f, 0.25f };
	spriteInstance.myPosition = { (myPosition.x) / resolution.myX, (myPosition.y) / resolution.myY };
	spriteInstance.mySize = { 0.1f,  0.1f };
	spriteInstance.myRotation = 0;
	spriteInstance.myColor = myColor;

	spriteDrawer.Draw(sharedData, spriteInstance);
	myBulletFactory.Render();
}


Player::~Player() = default;
