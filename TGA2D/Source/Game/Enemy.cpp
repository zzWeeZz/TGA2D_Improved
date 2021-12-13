#include "stdafx.h"
#include "Enemy.h"
#define SCREEN_SIZE_X static_cast<float>(Tga2D::CEngine::GetInstance()->GetTargetSize().myX)
#define SCREEN_SIZE_Y static_cast<float>(Tga2D::CEngine::GetInstance()->GetTargetSize().myY)

void Enemy::Init(const char* aSpritePath)
{
	myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(aSpritePath);
	mySize = { 0.1f, 0.1f };
	myPosition = { SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 };
	myDir = { 1, 0 };
	myGoRight = true;
}

void Enemy::Update(float aTimeDelta)
{
	myPosition.x += myDir.x * static_cast<float>(200) * aTimeDelta;
}

void Enemy::FlipDir()
{
	myDir.x *= -1;
	myPosition.y += 100;
	myGoRight = !myGoRight;
}

Vec2F Enemy::GetPosition()
{
	return myPosition;
}

void Enemy::SetPosition(float aX, float aY)
{
	myPosition = { aX, aY };
}

void Enemy::Render()
{
	auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	Tga2D::CSpriteDrawer& spriteDrawer(Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer());
	Tga2D::SSpriteSharedData sharedData = {};
	sharedData.myTexture = myTexture;

	Tga2D::SSpriteInstanceData spriteInstance = {};
	spriteInstance.myPivot = { 0.35f, 0.25f };
	spriteInstance.myPosition = { (myPosition.x) / resolution.myX, (myPosition.y) / resolution.myY };
	spriteInstance.mySize = Tga2D::Vector2f(mySize.x, mySize.y);
	spriteInstance.myRotation = 0;

	spriteDrawer.Draw(sharedData, spriteInstance);
}

bool Enemy::TimeToFlip()
{
	if(myPosition.x > SCREEN_SIZE_X && myGoRight)
	{
		return true;
	}
	if(myPosition.x < 0 && !myGoRight)
	{
		return true;
	}
	return false;
}
