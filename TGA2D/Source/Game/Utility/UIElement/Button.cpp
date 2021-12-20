#include "stdafx.h"
#include "Button.h"
#include "tga2d/texture/texture_manager.h"
#include "tga2d/texture/texture.h"


void Button::CreateButton(std::string aLabel, Tga2D::CText* aText, const CommonUtilities::Vector2<float> aPosition, const CommonUtilities::Vector2<float> aSize, const char* aTexturePath)
{
	myLabel = aLabel;
	myText = aText;
	myPosition = aPosition;
	mySize = aSize;
	myRotation = 0;
	myColor = { 1, 1, 1, 1 };
	mySprite.Init(&myPosition, &mySize, &myRotation, &myColor);
	myPoint[0] = { aPosition.x + aSize.x * 0.5f, aPosition.y + aSize.y * 0.5f };
	myPoint[1] = { aPosition.x + aSize.x * 0.5f, aPosition.y - aSize.y * 0.5f };
	myPoint[2] = { aPosition.x - aSize.x * 0.5f, aPosition.y - aSize.y * 0.5f };
	myPoint[3] = { aPosition.x - aSize.x * 0.5f, aPosition.y + aSize.y * 0.5f };
	mySprite.GiveSpritePath(aTexturePath);
	for (int i = 0; i < myPoint.size(); ++i)
	{
		if (i < 3)
		{
			CommonUtilities::Line<float> myLine(myPoint[i], myPoint[i + 1]);
			myLineVolume.AddLine(myLine);
		}
		else
		{
			CommonUtilities::Line<float> myLine(myPoint[i], myPoint[0]);
			myLineVolume.AddLine(myLine);
		}
	}
	const auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	myText->SetText(myLabel);
	myText->SetColor({ 0, 0, 0, 1 });
	float newPos = (myPosition.x - (myLabel.size() * 0.5f) * 9.5f);
	myText->SetPosition({ newPos/resolution.myX, myPosition.y/resolution.myY});
	
}

void Button::OnClick(void (*aFunction)(), const CommonUtilities::InputHandler& aInputHander)
{
	if (aInputHander.GetMouseButtonDown(0) && myLineVolume.IsInside({ static_cast<float>(aInputHander.GetMousePosition().x), static_cast<float>(aInputHander.GetMousePosition().y) }))
	{
		aFunction();
	}
}

void Button::Render()
{
	mySprite.Render();
	myText->Render();
}

Button::~Button()
{
	myText = nullptr;
	delete myText;
}
