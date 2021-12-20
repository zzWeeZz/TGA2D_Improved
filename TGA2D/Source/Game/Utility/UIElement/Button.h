#pragma once
#include "tga2d/text/text.h"
#include "tga2d/sprite/sprite.h"
#include <..\CommonUtilities\UtilityFunctions.hpp>
#include <..\CommonUtilities\LineVolume.hpp>
#include <..\CommonUtilities\Vector2.hpp>
#include "../Sprite/Sprite.h"
#include <../CommonUtilities/InputHandler.hpp>
#include <array>
#include <string>

class Button
{
public:
	Button() = default;
	void CreateButton(std::string aLabel, Tga2D::CText* aText, const CommonUtilities::Vector2<float> aPosition, const CommonUtilities::Vector2<float> aSize, const char* aTexturePath = "Sprites/square.dds");
	void OnClick(void (*aFunction)(), const CommonUtilities::InputHandler& aInputHander);
	void Render();
	~Button();
private:
	std::string myLabel;
	Tga2D::CText* myText;
	Sprite mySprite;
	CommonUtilities::LineVolume<float> myLineVolume;
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> mySize;
	float myRotation;
	Tga2D::CColor myColor;
	std::array<CommonUtilities::Vector2<float>, 4> myPoint;
};