#pragma once
#include "Enemy.h"

class EnemyFactory
{
public:
	void Init();
	void Update(float aTimeDelta);
	void Render();
	Enemy GetEnemy(int aRow, int aColum);
	bool Stop();

private:
	std::array<std::vector<Enemy>, 5> myColums;
	bool myGmaeover;
};
