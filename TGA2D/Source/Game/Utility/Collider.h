#pragma once
#include <..\CommonUtilities\Vector2.hpp>

class Collider
{
public:
	Collider();
	virtual void IsIntersected(const Collider* aCollider) = 0;
	virtual void DrawDebugLines() = 0;
	~Collider();
	CommonUtilities::Vector2<float>* myPosition;
	CommonUtilities::Vector2<float>* mySize;
	float* myRadius;
	bool myHasSomethingInside;
	int myId;
};