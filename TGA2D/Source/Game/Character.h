#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/InputHandler.hpp>
#include "Utility/Collider.h"
#include "Utility/CircleCollider.h"
#include "Utility/BoxCollider.h"

class Character
{
public:
	Character();
	void Init(int aLeftKey, int aRightKey, int aUpKey, int aDownKey, bool aCircle);
	void Update(float aTimeDelta, const CommonUtilities::InputHandler& aInputHandler);
	void Render();
	void DelegateCall();

private:

	int myLeftKey;
	int myRightKey;
	int myUpKey;
	int myDownKey;
	Tga2D::CTexture* myTexture;
	CircleCollider myCircleCollider;
	BoxCollider myBoxCollider;
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> mySize;
	Tga2D::CColor myColor;
	bool myIsCircle;
};
