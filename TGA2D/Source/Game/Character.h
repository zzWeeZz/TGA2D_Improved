#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/InputHandler.hpp>
#include "Utility/Collider.h"

class Character : public Collider
{
public:
	
	void Init();
	void Update(float aTimeDelta, const CommonUtilities::InputHandler& aInputHandler);
	void Render();
	

private:

	int myLeftKey;
	int myRightKey;
	Tga2D::CTexture* myTexture;
	Collider* myEnemyCollider;

	Tga2D::CColor myColor;
};
