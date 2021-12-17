
#include "stdafx.h"
#include "Collider.h"


Collider::Collider() : myPosition(nullptr), mySize(nullptr), myRadius(nullptr), myHasSomethingInside(false), myEnteredCollider(nullptr), myId(ColliderId::None) {}

Collider::~Collider()
{
	myPosition = nullptr;
	mySize = nullptr;
	myRadius = nullptr;
	myEnteredCollider = nullptr;
	delete myPosition;
	delete mySize;
	delete myRadius;
	delete myEnteredCollider;
}