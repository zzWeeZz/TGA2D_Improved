#include "stdafx.h"
#include "BulletFactory.h"

#include <iostream>


#define SCREEN_SIZE_X static_cast<float>(Tga2D::CEngine::GetInstance()->GetTargetSize().myX)
#define SCREEN_SIZE_Y static_cast<float>(Tga2D::CEngine::GetInstance()->GetTargetSize().myY)

BulletFactory::BulletFactory()
{
	myAmountOfBullets = 5;
	myFireRate = 0.5f;
}

BulletFactory::BulletFactory(int aAmountOfBullets, float aFireRate)
{
	myAmountOfBullets = aAmountOfBullets;
	myFireRate = aFireRate;
}

void BulletFactory::FireBullet(Vec2F aDiraction, Vec2F aPosition)
{
	if (myCurrentFireTimer > myFireRate)
	{
		if (myBullets.size() < myAmountOfBullets)
		{
			Bullet tempBullet;
			tempBullet.Init(aDiraction, aPosition, 200);
			myBullets.push_back(tempBullet);
		}
		else
		{
			std::cout << "Cant Fire more Bullets\n";
		}
		myCurrentFireTimer = 0;
	}
	else
	{
		std::cout << "Cant Fire yet!\n";
	}
}

void BulletFactory::Update(float aTimeDelta)
{
	myCurrentFireTimer += aTimeDelta;
	for (auto i = 0; i < myBullets.size(); ++i)
	{
		myBullets[i].Update(aTimeDelta);
		if (myBullets[i].GetPosition().x > SCREEN_SIZE_X || myBullets[i].GetPosition().x < 0 || myBullets[i].GetPosition().y > SCREEN_SIZE_Y || myBullets[i].GetPosition().y < 0)
		{
			myBullets.erase(myBullets.begin());
		}
	}
}

bool BulletFactory::DetectHit(Enemy aEnemy)
{
	for (auto i = 0; i < myBullets.size(); ++i)
	{
		if (myBullets[i].GetPosition().x < aEnemy.GetPosition().x + 100.f && myBullets[i].GetPosition().x + 100.f > aEnemy.GetPosition().x && myBullets[i].GetPosition().y < aEnemy.GetPosition().y + 100.f && myBullets[i].GetPosition().y + 100.f > aEnemy.GetPosition().y)
		{
			myBullets.erase(myBullets.begin());
			return true;
		}
	}
}

void BulletFactory::Render()
{
	for (auto bullet : myBullets)
	{
		bullet.Render();
	}
}


