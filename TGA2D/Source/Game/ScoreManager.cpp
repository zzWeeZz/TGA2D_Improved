#include "stdafx.h"
#include "ScoreManager.h"
#include <sstream>


ScoreManager::ScoreManager()
{

}

void ScoreManager::Init()
{
	myText = new Tga2D::CText("Text/arial.ttf", Tga2D::EFontSize_48);
	myRestartText = new Tga2D::CText("Text/arial.ttf", Tga2D::EFontSize_48);
	myRestartText->SetText("");
	myPlayerScore = 0;
	myAIScore = 0;
	std::ostringstream stringStream;
	stringStream << myPlayerScore << " | " << myAIScore << std::endl;
	std::string toString = stringStream.str();
	myText->SetText(toString);
	Tga2D::Vector2f textPos(0.44f, 0.1f);
	myText->SetPosition(textPos);
	myText->SetColor(Tga2D::CColor(1, 1, 1, 1));
}

int ScoreManager::GetPlayerScore() const
{
	return myPlayerScore;
}

int ScoreManager::GetAIScore() const
{
	return myAIScore;
}

bool ScoreManager::CheckIfGameIsOver()
{
	if (myAIScore >= 3 || myPlayerScore >= 3)
	{
		std::ostringstream stringStream;
		stringStream << "PRESS ENTER TO RESTART" << std::endl;
		std::string toString = stringStream.str();
		myRestartText->SetText(toString);
		Tga2D::Vector2f textPos(0.13f, 0.5f);
		myRestartText->SetPosition(textPos);
		myRestartText->SetColor(Tga2D::CColor(1, 1, 1, 1));
		return true;
	}
	return false;
}

void ScoreManager::Score(bool aIsPlayer)
{
	if (aIsPlayer)
	{
		myPlayerScore++;
	}
	else
	{
		myAIScore++;
	}
}

Tga2D::CText* ScoreManager::GetText()
{
	return myText;
}

Tga2D::CText* ScoreManager::GetRestartText()
{
	return myRestartText;
}

void ScoreManager::ResetScore()
{
	myPlayerScore = 0;
	myAIScore = 0;
	std::ostringstream stringStream;
	stringStream << myPlayerScore << " | " << myAIScore << std::endl;
	std::string toString = stringStream.str();
	myRestartText->SetText("");
	myText->SetText(toString);
}

void ScoreManager::UpdateText()
{
	std::ostringstream stringStream;
	stringStream << myPlayerScore << " | " << myAIScore << std::endl;
	std::string toString = stringStream.str();
	myText->SetText(toString);
}

ScoreManager::~ScoreManager()
{
	myText = nullptr;
	delete myText;
}