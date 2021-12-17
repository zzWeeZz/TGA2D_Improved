#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	void Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, CircleCollider& aCollider);
	void IsIntersected(Collider* aCollider) override;
	bool IntersectsWith(const Collider* aCollider) const;
	bool HasCollided(const Collider* aOutCollider) const;
	bool HasCollided() const;
	ColliderId GetId() const;
	void SetId(const ColliderId aID);
	void DrawDebugLines() override;
private:
	float myRadiusValue;
};