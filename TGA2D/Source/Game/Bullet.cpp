#include "stdafx.h"
#include "Bullet.h"


void Bullet::Init(Vec2F aDiraction, Vec2F aInitPos, int aSpeed)
{
	myDiraction = aDiraction;
	myPosition = aInitPos;
	mySpeed = aSpeed;
	myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("Sprites/shot1.dds");
}

void Bullet::Update(float aTimeDelta)
{
	myPosition += myDiraction * static_cast<float>(mySpeed) * aTimeDelta;
}

Vec2F Bullet::GetPosition()
{
	return myPosition;
}

void Bullet::Render()
{
	auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	Tga2D::CSpriteDrawer& spriteDrawer(Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer());
	Tga2D::SSpriteSharedData sharedData = {};
	sharedData.myTexture = myTexture;

	Tga2D::SSpriteInstanceData spriteInstance = {};
	spriteInstance.myPivot = { 0.25f, 0.25f };
	spriteInstance.myPosition = { (myPosition.x) / resolution.myX, (myPosition.y) / resolution.myY };
	spriteInstance.mySize = { 0.02f,  0.04f };
	spriteInstance.myRotation = 0;

	spriteDrawer.Draw(sharedData, spriteInstance);
}
