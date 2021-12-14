#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/LineVolume.hpp>
#include <array>


class Collider
{
public:
	Collider() = delete;
	Collider(CommonUtilities::Vector2<float>& aPosition, CommonUtilities::Vector2<float>& aSize);
	bool operator==(const Collider& aCollider) const;

	void UpdateCollider();

	bool OnEnter(const Collider& aCollider);
	bool OnStay(const Collider& aCollider) const;
	[[nodiscard]] bool OnExit(const Collider& aCollider);

private:
	CommonUtilities::Vector2<float>* myParentPosition;
	CommonUtilities::Vector2<float>* myParentSize;
	std::array<CommonUtilities::Vector2<float>, 4> myPoints;
	std::array<CommonUtilities::Line<float>, 4> myLines;
	CommonUtilities::LineVolume<float> myLineVolume;
};
