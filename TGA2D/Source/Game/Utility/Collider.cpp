#include "stdafx.h"
#include "Collider.h"
#include <algorithm>

#include "ColliderManager.h"

Collider globalCollider;
Collider::Collider()
{
	ColliderManager::GetInstance()->AddCollider(this);
}

#pragma warning(disable : 4100)
bool Collider::operator==(const Collider& aCollider) const
{
	return false;
}

std::vector<Collider> ObjectsInSideCollider;
std::vector<Collider> ObjectsPreviousFrame;
bool Collider::OnEnter(const Collider& aCollider)
{
	return false;
}

bool Collider::OnStay(const Collider& aCollider)
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
	
	return false;
}