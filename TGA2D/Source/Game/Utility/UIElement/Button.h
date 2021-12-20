#pragma once
#include "tga2d/text/text.h"
#include "tga2d/sprite/sprite.h"
#include <..\CommonUtilities\UtilityFunctions.hpp>
#include <..\CommonUtilities\LineVolume.hpp>
#include <..\CommonUtilities\Vector2.hpp>
#include "../Sprite/Sprite.h"
#include <../CommonUtilities/InputHandler.hpp>
#include <array>

class Button
{
public:
	Button() = default;
	void CreateButton(const char* aLabel, Tga2D::CText* aText, Sprite aSprite, const CommonUtilities::Vector2<float> aPosition, const CommonUtilities::Vector2<float> aSize);
	void OnClick(void (*aFunction)(), const CommonUtilities::InputHandler& aInputHander);
	void Render();
	~Button();
private:
	const char* myLabel;
	Tga2D::CText* myText;
	Sprite mySprite;
	CommonUtilities::LineVolume<float> myLineVolume;
	CommonUtilities::Vector2<float> myPosition;
	std::array<CommonUtilities::Vector2<float>, 4> myPoint;
};