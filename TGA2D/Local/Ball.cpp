#include "Ball.h"
#include <string>

Ball::Ball()
{
	myBallTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("sprites/ball.png");
}

void Ball::Update(float aDeltaTime)
{
}

void Ball::Render()
{
	Tga2D::CSpriteDrawer& spriteDrawer(Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer());
	Tga2D::SSpriteSharedData sharedData = {};
	sharedData.myTexture = myBallTexture;

	Tga2D::SSpriteInstanceData spriteInstance = {};
	spriteInstance.myPivot = myPivot;
	spriteInstance.myPosition = myPosition;
	spriteInstance.mySize = { 0.5f, 0.5f };

	spriteDrawer.Draw(sharedData, spriteInstance);
}

Ball::~Ball()
{
	delete myBallTexture;
	myBallTexture = nullptr;
}
