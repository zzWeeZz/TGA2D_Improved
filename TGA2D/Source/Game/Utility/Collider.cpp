
#include "stdafx.h"
#include "Collider.h"


Collider::Collider() : myPosition(nullptr), mySize(nullptr), myRadius(nullptr), myHasSomethingInside(false), myId(-1) {}

Collider::~Collider()
{
	myPosition = nullptr;
	mySize = nullptr;
	myRadius = nullptr;
	delete myPosition;
	delete mySize;
	delete myRadius;
}