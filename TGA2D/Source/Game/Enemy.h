#pragma once
#include "stdafx.h"
#include <vector>
#include <..\CommonUtilities\Vector2.hpp>
#include <..\CommonUtilities\LineVolume.hpp>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/drawers/sprite_drawer.h>
#include <tga2d/texture/texture_manager.h>
#include <tga2d/engine.h>



using Vec2F = CommonUtilities::Vector2<float>;
class Enemy
{
public:
	void Init(const char* aSpritePath);
	void Update(float aTimeDelta);
	void FlipDir();
	Vec2F GetPosition();
	void SetPosition(float aX, float aY);
	void Render();
	bool TimeToFlip();

private:
	Tga2D::CTexture* myTexture;
	Vec2F myDir;
	Vec2F myPosition;
	bool myGoRight;
	Vec2F mySize;
};
