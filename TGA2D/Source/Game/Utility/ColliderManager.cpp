#include "stdafx.h"
#include "ColliderManager.h"
#include <cassert>

ColliderManager* ColliderManager::myInstance = nullptr;
ColliderManager* ColliderManager::GetInstance()
{
	if (myInstance == nullptr)
	{
		myInstance = new ColliderManager();
	std::cout << "New ColliderManager has been created!\n";
	}
	return myInstance;
}

void ColliderManager::AddCollider(Collider* aCollider)
{
	myColliders.push_back(aCollider);
}

