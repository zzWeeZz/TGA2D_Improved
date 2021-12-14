#include "stdafx.h"
#include "Collider.h"
#include <algorithm>


Collider::Collider(CommonUtilities::Vector2<float>& aPosition, CommonUtilities::Vector2<float>& aSize) : myParentPosition(&aPosition), myParentSize(&aSize)
{
	myPoints[0] = { aPosition.x - aSize.x / 2, aPosition.y - aSize.y / 2 };
	myPoints[1] = { aPosition.x + aSize.x / 2, aPosition.y - aSize.y / 2 };
	myPoints[2] = { aPosition.x + aSize.x / 2, aPosition.y + aSize.y / 2 };
	myPoints[3] = { aPosition.x - aSize.x / 2, aPosition.y + aSize.y / 2 };
	for (int i = 0; i < 4; ++i)
	{
		if (i == 3)
		{
			myLines[i].InitWith2Points(myPoints[i], myPoints[0]);
		}
		else
		{
			myLines[i].InitWith2Points(myPoints[i], myPoints[i + 1]);
		}
		myLineVolume.AddLine(myLines[i]);
	}
}

bool Collider::operator==(const Collider& aCollider) const
{
	if (myParentPosition == aCollider.myParentPosition && myParentSize == aCollider.myParentSize)
	{
		return true;
	}
	return false;
}

void Collider::UpdateCollider()
{
	myPoints[0] = { myParentPosition->x - myParentSize->x / 2, myParentPosition->y - myParentSize->y / 2 };
	myPoints[1] = { myParentPosition->x + myParentSize->x / 2, myParentPosition->y - myParentSize->y / 2 };
	myPoints[2] = { myParentPosition->x + myParentSize->x / 2, myParentPosition->y + myParentSize->y / 2 };
	myPoints[3] = { myParentPosition->x - myParentSize->x / 2, myParentPosition->y + myParentSize->y / 2 };
	for (int i = 0; i < 4; ++i)
	{
		if (i == 3)
		{
			myLines[i].InitWith2Points(myPoints[i], myPoints[0]);
		}
		else
		{
			myLines[i].InitWith2Points(myPoints[i], myPoints[i + 1]);
		}
		myLineVolume.UpdateLines(myLines[i], i);
	}
}


std::vector<Collider> ObjectsInSideCollider;
std::vector<Collider> ObjectsPreviousFrame;
bool Collider::OnEnter(const Collider& aCollider)
{
	if (!(std::find(ObjectsInSideCollider.begin(), ObjectsInSideCollider.end(), aCollider) != ObjectsInSideCollider.end()))
	{
		for (int i = 0; i < 4; ++i)
		{
			if (myLineVolume.IsInside(aCollider.myPoints[i]))
			{
				ObjectsInSideCollider.push_back(aCollider);
				return true;
			}
		}
	}

	return false;
}

bool Collider::OnStay(const Collider& aCollider) const
{
	if (!(std::find(ObjectsInSideCollider.begin(), ObjectsInSideCollider.end(), aCollider) != ObjectsInSideCollider.end()))
	{
		return true;
	}
	return false;
}
#pragma warning(disable : 4834)
bool Collider::OnExit(const Collider& aCollider)
{
	for (int i = 0; i < 4; ++i)
	{
		if (std::find(ObjectsInSideCollider.begin(), ObjectsInSideCollider.end(), aCollider) != ObjectsInSideCollider.end() && !myLineVolume.IsInside(aCollider.myPoints[i]))
		{
			//std::remove(ObjectsInSideCollider.begin(), ObjectsInSideCollider.end(), aCollider);
			return true;
		}
	}
	return false;
}
