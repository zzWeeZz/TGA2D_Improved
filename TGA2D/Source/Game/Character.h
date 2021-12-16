#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/InputHandler.hpp>
#include "Utility/Collider.h"

class Character
{
public:
	Character();
	void Init(int aLeftKey, int aRightKey);
	void Update(float aTimeDelta, const CommonUtilities::InputHandler& aInputHandler);
	void Render();
	void DelegateCall();

private:

	int myLeftKey;
	int myRightKey;
	Tga2D::CTexture* myTexture;
	Collider myCollider;
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> mySize;
	Tga2D::CColor myColor;
};
