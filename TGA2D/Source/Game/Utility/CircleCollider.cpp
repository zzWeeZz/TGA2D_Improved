#include "stdafx.h"
#include "CircleCollider.h"
#include <tga2d/drawers/debug_drawer.h>
#include "UtilityFunctions.hpp"
#include "ColliderManager.h"

void CircleCollider::Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, CircleCollider& aCollider)
{
	myPosition = aPosition;
	mySize = aSize;
	myId = ColliderId::Circle;
	myRadiusValue = mySize->x / 2.0f;
	myRadius = &myRadiusValue;
	ColliderManager::GetInstance()->AddCollider(&aCollider);
}

void CircleCollider::IsIntersected(Collider* aCollider)
{
	if (aCollider->myRadius)
	{
		const float deltaX = (myPosition->x + *myRadius) - (aCollider->myPosition->x + *aCollider->myRadius);
		const float deltaY = (myPosition->y + *myRadius) - (aCollider->myPosition->y + *aCollider->myRadius);
		const auto distance = sqrt(deltaX * deltaX + deltaY * deltaY);

		if (distance < *myRadius + *aCollider->myRadius)
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
		const CommonUtilities::Vector2 distance = { CommonUtilities::Abs(myPosition->x - aCollider->myPosition->x),CommonUtilities::Abs(myPosition->y - aCollider->myPosition->y) };
		if (distance.x > (aCollider->mySize->x / 2 + *myRadius))
		{
			myHasSomethingInside = false;
			myEnteredCollider = nullptr;
			return;
			
		}
		if (distance.y > (aCollider->mySize->y / 2 + *myRadius))
		{
			myHasSomethingInside = false;
			myEnteredCollider = nullptr;
			return;
			
		}
		if (distance.x <= (aCollider->mySize->x / 2))
		{
			myHasSomethingInside = true;
			myEnteredCollider = aCollider;
			return;
		}
		if (distance.y <= (aCollider->mySize->y / 2))
		{
			myHasSomethingInside = true;
			myEnteredCollider = aCollider;
			return;
		}
		const float cDistSqrt = (distance.x - aCollider->mySize->x / 2) * (distance.x - aCollider->mySize->x / 2) + (distance.y - aCollider->mySize->y / 2) * (distance.y - aCollider->mySize->y / 2);


		if (cDistSqrt > (*myRadius * *myRadius))
		{
			myHasSomethingInside = false;
			myEnteredCollider = nullptr;
			return;
		}
		if (cDistSqrt <= (*myRadius * *myRadius))
		{
			myHasSomethingInside = true;
			myEnteredCollider = aCollider;
			
		}
		
	}
}


bool CircleCollider::IntersectsWith(const Collider* aCollider) const
{
	if (!aCollider->myRadius)
	{
		const float deltaX = (myPosition->x + *myRadius) - (aCollider->myPosition->x + *aCollider->myRadius);
		const float deltaY = (myPosition->y + *myRadius) - (aCollider->myPosition->y + *aCollider->myRadius);
		const auto distance = sqrt(deltaX * deltaX + deltaY * deltaY);

		if (distance < *myRadius + *aCollider->myRadius)
		{
			return  true;
		}
		else
		{
			return  false;
		}
	}
	else
	{
		const CommonUtilities::Vector2 distance = { CommonUtilities::Abs(myPosition->x - myPosition->x),CommonUtilities::Abs(myPosition->y - myPosition->y) };
		if (distance.x > (aCollider->mySize->x / 2 + *myRadius))
		{
			return  false;
		}
		if (distance.y > (aCollider->mySize->y / 2 + *myRadius))
		{
			return  false;
		}
		
		if (distance.x <= (aCollider->mySize->x / 2))
		{
			return  true;
		}
		if (distance.y <= (aCollider->mySize->y / 2))
		{
			return  true;
		}

		const float cDistSqrt = (distance.x - aCollider->mySize->x / 2) * (distance.x - aCollider->mySize->x / 2) + (distance.y - aCollider->mySize->y / 2) * (distance.y - aCollider->mySize->y / 2);

		std::cout << cDistSqrt << " " << (*myRadius * *myRadius) << std::endl;

		if (cDistSqrt > (*myRadius * *myRadius))
		{
			return false;
		}
		if (cDistSqrt < (*myRadius * *myRadius))
		{
			return true;
		}
	
	}
	return false;
}

bool CircleCollider::HasCollided(const Collider* aOutCollider) const
{
	aOutCollider = myEnteredCollider;
	return myHasSomethingInside;
}

bool CircleCollider::HasCollided() const
{
	return myHasSomethingInside;
}

ColliderId CircleCollider::GetId() const
{
	return myId;
}

void CircleCollider::SetId(const ColliderId aID)
{
	myId = aID;
}

void CircleCollider::DrawDebugLines()
{
	const auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawCircle({ myPosition->x / resolution.myX, myPosition->y / resolution.myY }, *myRadius / resolution.myX, { 1, 0, 0, 1 });
}
