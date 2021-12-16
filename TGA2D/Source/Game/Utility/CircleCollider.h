#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	void Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, CircleCollider& aCollider);
	void IsIntersected(const Collider* aCollider) override;
	bool IntersectsWith(const Collider* aCollider) const;
	bool hasCollided() const;
	int GetId() const;
	void SetId(const int aID);
	void DrawDebugLines() override;
private:
	float myRadiusValue;
};