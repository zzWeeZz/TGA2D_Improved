#include "stdafx.h"
#include "ColliderManager.h"
#include <cassert>
#include <tga2d/drawers/debug_drawer.h>


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

void ColliderManager::UpdateCollision() const
{
	for (auto i = 0; i < myColliders.size(); ++i)
	{
		if (myColliders[i])
		{
			for (auto collider : myColliders)
			{
				if (myColliders[i] != collider)
				{
					myColliders[i]->IsIntersects(collider);
					continue;
				}
			}
		}
#ifdef _DEBUG
		myColliders[i]->DrawDebugLines();
#endif
	}

}

void ColliderManager::EnableDebug()
{
	myDebug = true;
}

