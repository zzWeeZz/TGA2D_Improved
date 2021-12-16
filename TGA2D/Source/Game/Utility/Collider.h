#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/LineVolume.hpp>
#include <array>

class Collider;

class Collider
{
public:
	Collider() = default;
	void Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, Collider& aCollider);
	void IsIntersects(const Collider* aCollider);
	bool IntersectsWith(const Collider* aCollider) const;
	bool HasCollided() const;
	int GetId() const;
	void SetId(const int aID);
	void DrawDebugLines();
	
private:
	CommonUtilities::Vector2<float>* myPosition;
	CommonUtilities::Vector2<float>* mySize;
	Tga2D::Vector2<float> myBotRight;
	Tga2D::Vector2<float> myBotLeft;
	Tga2D::Vector2<float> myTopLeft;
	Tga2D::Vector2<float> myTopRight;

	int myId;
	bool myHasSomethingInside;
};