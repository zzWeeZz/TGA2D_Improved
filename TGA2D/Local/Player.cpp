#include "Player.h"


Player::Player()
{
	GetPlayerVector().Set(0.1f, 0.5f);
}

void Player::Init()
{
	myBox.GetPosition().Set(0.1f, 0.5f);
}

Box Player::GetBox()
{
	return myBox;
}

Tga2D::Vector2f Player::GetPlayerVector()
{
	return myPlayerVector;
}

void Player::Update(float aTimeDelta, CommonUtilities::InputHandler& aInputHandler)
{
	myBox.MoveBox(myPlayerVector);
	if (aInputHandler.KeyIsPressed(W_KEY))
	{
		myPlayerVector.myY -= aTimeDelta;
	}
	if (aInputHandler.KeyIsPressed(S_KEY))
	{
		myPlayerVector.myY += aTimeDelta;
	}
}
