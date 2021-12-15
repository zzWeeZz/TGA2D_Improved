#pragma once
#include "Collider.h"


class ColliderManager
{
public:
	ColliderManager(ColliderManager& other) = delete;
	void operator=(const ColliderManager&) = delete;
	static ColliderManager* GetInstance();
	void AddCollider(Collider* aCollider);


private:
	ColliderManager() = default;
	std::vector<Collider*> myColliders;
	static ColliderManager* myInstance;
};
