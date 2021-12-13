#pragma once
#include "stdafx.h"
#include <string>

#include <tga2d/text/text.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/shaders/sprite_shader.h>
class ScoreManager
{
public:
	ScoreManager();
	void Init();
	int GetPlayerScore() const;
	int GetAIScore() const;
	bool CheckIfGameIsOver();
	void Score(bool aIsPlayer);
	Tga2D::CText* GetText();
	Tga2D::CText* GetRestartText();
	void ResetScore();
	void UpdateText();

	~ScoreManager();

private:
	int myPlayerScore;
	int myAIScore;
	Tga2D::CText* myText;
	Tga2D::CText* myRestartText;
};