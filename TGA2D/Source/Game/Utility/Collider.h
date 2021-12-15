#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/LineVolume.hpp>
#include <array>
#include "Delegate.hpp"



class Collider
{
public:
	Collider();
	bool operator==(const Collider& aCollider) const;

	bool OnEnter(const Collider& aCollider);
	bool OnStay(const Collider& aCollider);
	bool OnExit(const Collider& aCollider);
protected:
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> mySize;

};
Delegate<void(const Collider&)> delegate;