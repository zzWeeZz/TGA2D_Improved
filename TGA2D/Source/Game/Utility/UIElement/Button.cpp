#include "stdafx.h"
#include "Button.h"
#include "tga2d/texture/texture_manager.h"
#include "tga2d/texture/texture.h"


void Button::CreateButton(const char* aLabel, Tga2D::CText* aText, Sprite aSprite, const CommonUtilities::Vector2<float> aPosition, const CommonUtilities::Vector2<float> aSize)
{
	myLabel = aLabel;
	myText = aText;
	mySprite = aSprite;
	myPosition = aPosition;
	myPoint[0] = { aPosition.x + aSize.x, aPosition.y + aSize.y };
	myPoint[1] = { aPosition.x + aSize.x, aPosition.y - aSize.y };
	myPoint[2] = { aPosition.x - aSize.x, aPosition.y - aSize.y };
	myPoint[3] = { aPosition.x - aSize.x, aPosition.y + aSize.y };
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
	myText->SetPosition({ myPosition.x/resolution.myX, myPosition.y/resolution.myY});
	
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
	myLabel = nullptr;
	myText = nullptr;
	delete myLabel;
	delete myText;
}
