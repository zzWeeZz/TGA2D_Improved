#include "stdafx.h"
#include "EnemyFactory.h"

#define SCREEN_SIZE_X static_cast<float>(Tga2D::CEngine::GetInstance()->GetTargetSize().myX)
#define SCREEN_SIZE_Y static_cast<float>(Tga2D::CEngine::GetInstance()->GetTargetSize().myY)

void EnemyFactory::Init()
{
	for (int j = 0; j < myColums.size(); ++j)
	{
		for (int i = 0; i < 7; ++i)
		{
			Enemy tempEnemy;
			if (i < 3)
			{
				tempEnemy.Init("Sprites/enemy3.dds");
			}
			else if (i >= 3 && i < 6)
			{
				tempEnemy.Init("Sprites/enemy2.dds");
			}
			else
			{
				tempEnemy.Init("Sprites/enemy1.dds");
			}
			tempEnemy.SetPosition((j + 1) * 100, (i + 1) * 50);
			myColums[j].push_back(tempEnemy);
		}
	}
}

void EnemyFactory::Update(float aTimeDelta)
{
	for (int j = 0; j < myColums.size(); ++j)
	{
		for (int i = 0; i < myColums[j].size(); ++i)
		{
			myColums[j][i].Update(aTimeDelta);
		}
	}
	if(myColums[4][0].TimeToFlip() || myColums[0][0].TimeToFlip())
	{
		for (int j = 0; j < myColums.size(); ++j)
		{
			for (int i = 0; i < myColums[j].size(); ++i)
			{
				myColums[j][i].FlipDir();
			}
		}
	}
}

void EnemyFactory::Render()
{
	for (int j = 0; j < myColums.size(); ++j)
	{
		for (int i = 0; i < myColums[j].size(); ++i)
		{
			myColums[j][i].Render();
		}
	}
}

Enemy EnemyFactory::GetEnemy(int aRow, int aColum)
{
	return myColums[aRow][aColum];
}

bool EnemyFactory::Stop()
{
	for (int j = 0; j < myColums.size(); ++j)
	{
		for (int i = 0; i < myColums[j].size(); ++i)
		{
			if (myColums[j][i].GetPosition().y == 720 - 100)
			{
				return true;
			}
		}
	}
	return false;
}
