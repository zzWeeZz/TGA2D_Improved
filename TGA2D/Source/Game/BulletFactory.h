#pragma once
#include "Bullet.h"
#include "Enemy.h"

class BulletFactory
{
public:
	BulletFactory();
	BulletFactory(int aAmountOfBullets, float aFireRate);
	void FireBullet(Vec2F aDiraction, Vec2F aPosition);
	void Update(float aTimeDelta);
	bool DetectHit(Enemy aEnemy);
	void Render();

private:
	std::vector<Bullet> myBullets;
	float myFireRate;
	float myCurrentFireTimer;
	int myAmountOfBullets;
};
