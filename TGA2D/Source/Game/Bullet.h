#pragma once
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/drawers/sprite_drawer.h>
#include <tga2d/texture/texture_manager.h>
#include <tga2d/engine.h>
#include <../CommonUtilities/Vector2.hpp>

using Vec2F = CommonUtilities::Vector2<float>;
class Bullet
{
public:
	void Init(Vec2F aDiraction, Vec2F aInitPos, int aSpeed);
	void Update(float aTimeDelta);
	Vec2F GetPosition();
	void Render();

private:
	int mySpeed;
	Vec2F myPosition;
	Vec2F myDiraction;
	Tga2D::CTexture* myTexture;
};
