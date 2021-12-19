#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/InputHandler.hpp>
#include "Utility/Collider.h"
#include "Utility/CircleCollider.h"
#include "Utility/BoxCollider.h"
#include "Utility/Sprite/Sprite.h"
#include "Utility/GameObject/GameObject.h"

class Character : public GameObject
{
public:
	void Init(int aLeftKey, int aRightKey, int aUpKey, int aDownKey, bool aCircle);
	void Update(float aTimeDelta, const CommonUtilities::InputHandler& aInputHandler);
	void Render();
	void DelegateCall();

private:

	int myLeftKey;
	int myRightKey;
	int myUpKey;
	int myDownKey;
	CircleCollider myCircleCollider;
	BoxCollider myBoxCollider;
	bool myIsCircle;
};
