#pragma once
#include "..\Game\Box.h"
#include <InputHandler.hpp>

class Player
{
public:
	Player();
	void Init();
	Box GetBox();
	void Update(float aTimeDelta, CommonUtilities::InputHandler& aInputHandler);
	Tga2D::Vector2f GetPlayerVector();
	~Player();
private:
	Box myBox;
	Tga2D::Vector2f myPlayerVector;
};