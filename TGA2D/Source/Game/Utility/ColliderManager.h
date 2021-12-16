#pragma once
#include "Collider.h"


class ColliderManager
{
public:
	ColliderManager(ColliderManager& other) = delete;
	void operator=(const ColliderManager&) = delete;
	static ColliderManager* GetInstance();
	void AddCollider(Collider* aData);
	//void RemoveCollider(Collider* aData);
	void UpdateCollision() const;
	void EnableDebug();

private:
	ColliderManager() = default;
	std::vector<Collider*> myColliders;
	static ColliderManager* myInstance;
	bool myDebug = false;
};
