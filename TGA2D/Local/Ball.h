#pragma once
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/drawers/sprite_drawer.h>
#include <tga2d/texture/texture_manager.h>
#include <tga2d/engine.h>
#pragma once


namespace Tga2D
{
	class CTexture;
}


class Ball
{
public:
	Ball();

	void Update(float aDeltaTime);
	void Render();

	~Ball();

private:
	Tga2D::CTexture* myBallTexture;
	Tga2D::Vector2f myPosition;
	Tga2D::Vector2f myPivot;
	float myRotation;
};