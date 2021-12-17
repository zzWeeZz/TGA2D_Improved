#pragma once
#include <..\CommonUtilities\Vector2.hpp>


enum class ColliderId
{
	None = 0,
	Box = 1,
	Circle = 1 << 1,
};

class Collider
{
public:
	Collider();
	virtual void IsIntersected(Collider* aCollider) = 0;
	virtual void DrawDebugLines() = 0;
	virtual ~Collider();
	CommonUtilities::Vector2<float>* myPosition;
	CommonUtilities::Vector2<float>* mySize;
	float* myRadius;
	bool myHasSomethingInside;
	const Collider* myEnteredCollider;
	ColliderId myId;
};