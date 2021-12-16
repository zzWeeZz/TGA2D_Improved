#include "stdafx.h"
#include "Collider.h"
#include <algorithm>
#include <tga2d/drawers/debug_drawer.h>
#include "ColliderManager.h"

void Collider::Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, Collider& aCollider)
{
	ColliderManager::GetInstance()->AddCollider(&aCollider);
	myPosition = aPosition;
	mySize = aSize;
}

void Collider::IsIntersects(const Collider* aCollider)
{
	if (myPosition->x < aCollider->myPosition->x + aCollider->mySize->x &&
		myPosition->x + mySize->x > aCollider->myPosition->x &&
		myPosition->y < aCollider->myPosition->y + aCollider->mySize->y &&
		myPosition->y + mySize->y > aCollider->myPosition->y)
	{
		myHasSomethingInside = true;
	}
	else
		myHasSomethingInside = false;

}

bool Collider::IntersectsWith(const Collider* aCollider) const
{

	if (myPosition->x < aCollider->myPosition->x + aCollider->mySize->x &&
		myPosition->x + mySize->x > aCollider->myPosition->x &&
		myPosition->y < aCollider->myPosition->y + aCollider->mySize->y &&
		myPosition->y + mySize->y > aCollider->myPosition->y)
	{
		return true;
	}
	return false;
}

bool Collider::HasCollided() const
{
	return myHasSomethingInside;
}

int Collider::GetId() const
{
	return myId;
}

void Collider::SetId(const int aID)
{
	myId = aID;
}

void Collider::DrawDebugLines()
{
	auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	myBotRight = { (myPosition->x + mySize->x / 2) / resolution.myX, (myPosition->y + mySize->y / 2) / resolution.myY };
	myBotLeft = { (myPosition->x - mySize->x / 2) / resolution.myX, (myPosition->y + mySize->y / 2) / resolution.myY };
	myTopLeft = { (myPosition->x - mySize->x / 2) / resolution.myX, (myPosition->y - mySize->y / 2) / resolution.myY };
	myTopRight = { (myPosition->x + mySize->x / 2) / resolution.myX, (myPosition->y - mySize->y / 2) / resolution.myY };
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(myBotRight, myBotLeft, { 1, 0, 0, 1 });

	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(myBotLeft, myTopLeft, { 1, 0, 0, 1 });

	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(myTopLeft, myTopRight, { 1, 0, 0, 1 });

	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(myTopRight, myBotRight, { 1, 0, 0, 1 });

}
