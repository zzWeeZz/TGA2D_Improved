#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/InputHandler.hpp>
#include "Utility/CircleCollider.h"
#include "Utility/BoxCollider.h"
#include "Utility/GameObject/GameObject.h"
#include "Utility/UIElement/Button.h"

class Character : public GameObject
{
public:
	void Init(int aLeftKey, int aRightKey, int aUpKey, int aDownKey, bool aCircle);
	void Update(float aTimeDelta, const CommonUtilities::InputHandler& aInputHandler);
	void Render();

private:

	int myLeftKey;
	int myRightKey;
	int myUpKey;
	int myDownKey;
	Tga2D::CText* myText;
	Button myButton;
	CircleCollider myCircleCollider;
	BoxCollider myBoxCollider;
	bool myIsCircle;
};
