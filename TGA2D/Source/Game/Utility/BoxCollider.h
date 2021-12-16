#pragma once
#include "stdafx.h"
#include <..\CommonUtilities/LineVolume.hpp>
#include <array>
#include "Collider.h"

class BoxCollider;

class BoxCollider : public Collider
{
public:
	BoxCollider() = default;
	void Init(CommonUtilities::Vector2<float>* aPosition, CommonUtilities::Vector2<float>* aSize, BoxCollider& aCollider);
	void IsIntersected(const Collider* aCollider) override;
	bool IntersectsWith(const Collider* aCollider) const;
	bool HasCollided() const;
	int GetId() const;
	void SetId(const int aID);
	void DrawDebugLines() override;
	
private:
	Tga2D::Vector2<float> myBotRight;
	Tga2D::Vector2<float> myBotLeft;
	Tga2D::Vector2<float> myTopLeft;
	Tga2D::Vector2<float> myTopRight;


};