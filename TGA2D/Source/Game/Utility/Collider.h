#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/LineVolume.hpp>

using Vec2F = CommonUtilities::Vector2<float>;

class Collider
{
public:
	Collider() = delete;
	Collider(const Vec2F& aPosition);
	Collider(const Vec2F& aPosition, const Vec2F& aSize);
	void UpdateCollider();
	bool OnEnter(const Collider& aCollider);
	bool OnStay(const Collider& aCollider) const;
	bool OnExit(const Collider& aCollider);

private:
	Vec2F myParentPosition;
	Vec2F myParentSize;
	std::array<CommonUtilities::Vector2<float>, 4> myPoints;
	CommonUtilities::LineVolume<float> myLineVolume;
};
