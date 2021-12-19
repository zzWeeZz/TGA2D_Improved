#include "stdafx.h"
#include "BoxCollider.h"
#include <algorithm>
#include <tga2d/drawers/debug_drawer.h>
#include <../CommonUtilities/UtilityFunctions.hpp>
#include "ColliderManager.h"

void BoxCollider::Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, BoxCollider& aCollider)
{
	ColliderManager::GetInstance()->AddCollider(&aCollider);
	myId = ColliderId::Box;
	myPosition = aPosition;
	mySize = aSize;
}

void BoxCollider::IsIntersected(Collider* aCollider)
{
	if (!aCollider->myRadius)
	{

		if (myPosition->x < aCollider->myPosition->x + aCollider->mySize->x &&
			myPosition->x + mySize->x > aCollider->myPosition->x &&
			myPosition->y < aCollider->myPosition->y + aCollider->mySize->y &&
			myPosition->y + mySize->y > aCollider->myPosition->y)
		{
			myHasSomethingInside = true;
			myEnteredCollider = aCollider;
		}
		else
		{
			myHasSomethingInside = false;
			myEnteredCollider = nullptr;
		}
	}
	else
	{
		const CommonUtilities::Vector2 distance = { CommonUtilities::Abs(aCollider->myPosition->x - myPosition->x),CommonUtilities::Abs(aCollider->myPosition->y - myPosition->y) };
		if(distance.x > (mySize->x/2 + *aCollider->myRadius))
		{
			myHasSomethingInside = false;
			myEnteredCollider = nullptr;
			return;
		}
		if(distance.y > (mySize->y / 2 + *aCollider->myRadius))
		{
			myHasSomethingInside = false;
			myEnteredCollider = nullptr;
			return;
		}
		if (distance.x <= (mySize->x / 2))
		{
			myHasSomethingInside = true;
			myEnteredCollider = aCollider;
			return;
		}
		if (distance.y <= (mySize->y / 2))
		{
			myHasSomethingInside = true;
			myEnteredCollider = aCollider;
			return;
		}
		
		const float cDistSqrt = (distance.x - mySize->x / 2) * (distance.x - mySize->x / 2) + (distance.y - mySize->y / 2) * (distance.y - mySize->y / 2);
		if (cDistSqrt > (*aCollider->myRadius * *aCollider->myRadius))
		{
			myHasSomethingInside = false;
			myEnteredCollider = nullptr;
			return;
		}

		if(cDistSqrt <= (*aCollider->myRadius * *aCollider->myRadius))
		{
			myHasSomethingInside = true;
			myEnteredCollider = aCollider;
			return;
		}
		
	}
}

bool BoxCollider::IntersectsWith(const Collider* aCollider) const
{

	if (myPosition->x < aCollider->myPosition->x + aCollider->mySize->x &&
		myPosition->x + mySize->x > aCollider->myPosition->x &&
		myPosition->y < aCollider->myPosition->y + aCollider->mySize->y &&
		myPosition->y + mySize->y > aCollider->myPosition->y)
	{
		return true;
	}
	else
	{
		const CommonUtilities::Vector2 distance = { CommonUtilities::Abs(aCollider->myPosition->x - myPosition->x),CommonUtilities::Abs(aCollider->myPosition->y - myPosition->y) };
		if (distance.x > (mySize->x / 2 + *aCollider->myRadius))
		{
			return false;
		}
		if (distance.y > (mySize->y / 2 + *aCollider->myRadius))
		{
			return false;
		}
		if (distance.x <= (mySize->x / 2))
		{
			return true;
		}
		if (distance.y <= (mySize->y / 2))
		{
			return true;
		}
		const float cDistSqrt = (distance.x - mySize->x / 2) * (distance.x - mySize->x / 2) + (distance.y - mySize->y / 2) * (distance.y - mySize->y / 2);
		if (cDistSqrt > (*aCollider->myRadius * *aCollider->myRadius))
		{
			return false;
		}
		if (cDistSqrt <= (*aCollider->myRadius * *aCollider->myRadius))
		{
			return true;
		}
	}
	return false;
}

bool BoxCollider::HasCollided(const Collider* aOutCollider) 
{
	 aOutCollider = myEnteredCollider;
	return myHasSomethingInside;
}

bool BoxCollider::HasCollided() const
{
	return myHasSomethingInside;
}

ColliderId BoxCollider::GetId() const
{
	return myId;
}

void BoxCollider::SetId(const ColliderId aID)
{
	myId = aID;
}

void BoxCollider::DrawDebugLines()
{
	const auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	myBotRight = { (myPosition->x + mySize->x / 2) / resolution.myX, (myPosition->y + mySize->y / 2) / resolution.myY };
	myBotLeft = { (myPosition->x - mySize->x / 2) / resolution.myX, (myPosition->y + mySize->y / 2) / resolution.myY };
	myTopLeft = { (myPosition->x - mySize->x / 2) / resolution.myX, (myPosition->y - mySize->y / 2) / resolution.myY };
	myTopRight = { (myPosition->x + mySize->x / 2) / resolution.myX, (myPosition->y - mySize->y / 2) / resolution.myY };
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(myBotRight, myBotLeft, { 1, 0, 0, 1 });

	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(myBotLeft, myTopLeft, { 1, 0, 0, 1 });

	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(myTopLeft, myTopRight, { 1, 0, 0, 1 });

	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(myTopRight, myBotRight, { 1, 0, 0, 1 });

}

BoxCollider::~BoxCollider()
{
}
