#include "stdafx.h"
#include "Collider.h"
#include <algorithm>


Collider::Collider(const Vec2F& aPosition) : myParentPosition(aPosition), myParentSize(150, 150)
{
	myPoints[0] = { aPosition.x - myParentSize.x / 2, aPosition.y - myParentSize.y / 2 };
	myPoints[1] = { aPosition.x + myParentSize.x / 2, aPosition.y - myParentSize.y / 2 };
	myPoints[2] = { aPosition.x + myParentSize.x / 2, aPosition.y + myParentSize.y / 2 };
	myPoints[3] = { aPosition.x - myParentSize.x / 2, aPosition.y + myParentSize.y / 2 };
	for (int i = 0; i < 4; ++i)
	{
		CommonUtilities::Line<float> tempLine;
		tempLine.InitWith2Points(myPoints[i], myPoints[1 + i]);
		myLineVolume.AddLine(tempLine);
	}
}

Collider::Collider(const Vec2F& aPosition, const Vec2F& aSize) : myParentPosition(aPosition), myParentSize(aSize)
{
	myPoints[0] = { aPosition.x - aSize.x / 2, aPosition.y - aSize.y / 2 };
	myPoints[1] = { aPosition.x + aSize.x / 2, aPosition.y - aSize.y / 2 };
	myPoints[2] = { aPosition.x + aSize.x / 2, aPosition.y + aSize.y / 2 };
	myPoints[3] = { aPosition.x - aSize.x / 2, aPosition.y + aSize.y / 2 };
	for (int i = 0; i < 4; ++i)
	{
		CommonUtilities::Line<float> tempLine;
		if (i == 3)
		{
			tempLine.InitWith2Points(myPoints[i], myPoints[0]);
		}
		else
		{
			tempLine.InitWith2Points(myPoints[i], myPoints[i + 1]);
		}
		myLineVolume.AddLine(tempLine);
	}
}

std::vector<Collider> ObjectsInSideCollider;
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
			else
			{
				std::remove(ObjectsInSideCollider.begin(), ObjectsInSideCollider.end(), aCollider);
			}
		}
	}

	return false;
}

bool Collider::OnStay(const Collider& aCollider) const
{
	if (std::find(ObjectsInSideCollider.begin(), ObjectsInSideCollider.end(), aCollider) != ObjectsInSideCollider.end())
	{
		return true;
	}
	return false;
}

bool Collider::OnExit(const Collider& aCollider)
{

}
