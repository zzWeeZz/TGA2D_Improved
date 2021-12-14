#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/InputHandler.hpp>
#include "Utility/Collider.h"

class Character
{
public:
	Character(int aLeftKey, int aRightKey, Collider* aEnemyCollider);
	void Init();
	void Update(float aTimeDelta, const CommonUtilities::InputHandler& aInputHandler);
	void Render();
	Collider myCollider;

private:
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> mySize;

	int myLeftKey;
	int myRightKey;
	Tga2D::CTexture* myTexture;
	Collider* myEnemyCollider;

	Tga2D::CColor myColor;
};
